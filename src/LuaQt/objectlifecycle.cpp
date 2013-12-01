/****************************************************************************
**
** Copyright (C) 2013 tdzl2003.
** Contact: https://github.com/tdzl2003/luaqt
**
** This file is part of the LuaQt Toolkit source.
**
** This file is licensed at BSD New license.
**
** NOTICE:
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
** POSSIBILITY OF SUCH DAMAGE.** 
**
** read COPYRIGHT.md for more informations.
**
****************************************************************************/

#include <LuaQt/globals.hpp>
#include <QtCore/qobject.h>
#include <QtCore/qvariant.h>
#include <stdlib.h>
#include <assert.h>

// Currently, LuaJIT 2.0 has no __gc support for "table" type.
// So do something ugly.
// LuaJIT 2.1 will solve this problem. Do something then.
namespace LuaQt{

	Q_DECL_EXPORT bool isObject(lua_State *L, int idx, const char* className)
	{
		if (lua_isnil(L, idx)){
			return true;
		}
		if (!lua_istable(L, idx)){
			return false;
		}
		lua_getfield(L, idx, className);
		bool ret = lua_islightuserdata(L, -1);
		lua_pop(L, 1);
		return ret;
	}

	Q_DECL_EXPORT void* checkObject(lua_State *L, int idx, const char* className)
	{
		if (lua_isnil(L, idx)){
			return NULL;
		}
		if (!lua_istable(L, idx)){
			luaL_error(L, "Argument %d is not a `%s` object.", idx, className);
		}
		lua_getfield(L, idx, className);
		if (!lua_islightuserdata(L, -1)){
			luaL_error(L, "Argument %d is not a `%s` object.", idx, className);
		}
		void* ret = lua_touserdata(L, -1);
		lua_pop(L, 1);
		return ret;
	}

	class  QLuaQtUserData
		: public QObjectUserData
	{
	public:
		lua_State *L;
		int lua_ref;
	};

	Q_DECL_EXPORT void PushObject(lua_State *L, QObject* obj)
	{
		QLuaQtUserData* userData = (QLuaQtUserData*) obj->userData(0);
		if (!userData){
			//TODO: Get className from meta-object and init it.
			// use obj->metaObject()->className
			luaL_error(L, "Object has no lua reference.");
		}
		getweakref(L, userData->lua_ref);
	}

	static void onDestroyed(QObject* obj)
	{
		QLuaQtUserData* userData = (QLuaQtUserData*) obj->userData(0);
		obj->setUserData(0, NULL);

		assert(userData);
		lua_State *L = userData->L;
		int ref = userData->lua_ref;
		getweakref(L, ref);
		delete userData;

		if (lua_istable(L, -1)){
			weakunref(L, ref);
			//TODO: clean lightuserdata pointer in table.

			//remove gcer.
			lua_pushliteral(L, "__gcer");
			lua_rawget(L, -2);
			QObject** ppobj = (QObject**)lua_touserdata(L, 1);
			if (ppobj) {
				*ppobj = NULL;
			}
			lua_pop(L, 1);

			lua_pop(L, 1);
		} else {
			lua_pop(L, 1);
		}
	}

	static int gcer(lua_State *L)
	{
		QObject** ppobj = (QObject**)lua_touserdata(L, 1);
		QObject* obj = *ppobj;
		*ppobj = NULL;
		delete obj;
		return 0;
	}

#define GCer "LuaQtGCer"

	void Q_DECL_EXPORT InitGCer(lua_State *L)
	{
		luaL_newmetatable(L, GCer);
		lua_pushcfunction(L, gcer);
		lua_setfield(L, -2, "__gc");
		lua_pop(L, 1);
	}

	Q_DECL_EXPORT void InitAndPushObject(lua_State *L, QObject* obj, void* ptr, const char* className)
	{
		// create object.
		lua_createtable(L, 0, 1);
		lua_pushstring(L, className);
		lua_pushlightuserdata(L, ptr);
		lua_rawset(L, -3);

		lua_pushliteral(L, "__gcer");
		QObject** ppobj = (QObject**)lua_newuserdata(L, sizeof(QObject*));
		(*ppobj) = obj;
		luaL_getmetatable(L, GCer);
		lua_setmetatable(L, -2);
		lua_rawset(L, -3);
		
		luaL_getmetatable(L, className);
		lua_setmetatable(L, -2);

		// listen "destroyed" signal
		obj->connect(obj, &QObject::destroyed, onDestroyed);

		// get weak reference id.
		// There's no LUA_RIDX_MAINTHREAD in luajit now,
		// so DONOT require any module in coroutine thread!
		QLuaQtUserData* userData = new QLuaQtUserData();
		userData->L = getGlobalState(L);
		lua_pushvalue(L, -1);
		userData->lua_ref = weakref(L);
		obj->setUserData(0, userData);
	}

}