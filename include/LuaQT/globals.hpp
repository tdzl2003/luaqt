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

#pragma once

#include <lua.hpp>

// Utility functions
inline void luaL_regfuncs(lua_State*L, luaL_Reg* reg, size_t count)
{
	for (size_t i =0; i < count; ++i)
	{
		lua_pushcfunction(L, reg[i].func);
		lua_setfield(L, -2, reg[i].name);
	}
}

#define luaL_newlib(l, m)  lua_createtable(l, 0, sizeof(m)/sizeof(m[0]) - 1); luaL_regfuncs(l, m, sizeof(m)/sizeof(m[0]) - 1)

namespace LuaQt{
	void saveGlobalState(lua_State *L);
	lua_State* getGlobalState(lua_State *L);
}

// Weak ref functions
namespace LuaQt{
	int weakref(lua_State *L);
	void getweakref(lua_State *L, int id);
	void weakunref(lua_State *L, int id);
}

// Object life-cycle functions
class QObject;
namespace LuaQt{
	bool isObject(lua_State *L, int idx, const char* className);
	void* checkObject(lua_State *L, int idx, const char* className);

	void PushObject(lua_State *L, QObject* obj);
	void InitAndPushObject(lua_State *L, QObject* obj, void* ptr, const char* className);

	void InitGCer(lua_State *L);
}


// Meta functions:
namespace LuaQt{
	int General_index(lua_State *L);
	int General_newindex(lua_State *L);
}

// Argument helper functions&macros
namespace LuaQt
{
	template <typename T>
	class ArgHelper
	{
	public:
		static bool CheckArg(lua_State *L, int idx);
		static T GetArg(lua_State *L, int idx);
		static void pushRetVal(lua_State*L, const T& val);
		static void pushRetVal(lua_State*L, T&& val);
	};

	void StartArgRefFrame(lua_State *L);
	void EndArgRefFrame(lua_State *L);

	void* allocArgRef(lua_State *L, size_t size);
}

#define CHECK_ARG_COUNT(c) if (lua_gettop(L) != c) { break; }
#define CHECK_ARG(t, i) if (!LuaQt::ArgHelper<t>::CheckArg(L, i)) { break;}
#define GET_ARG(t, i, n) t n = LuaQt::ArgHelper<t>::GetArg(L, i)

#define CHECK_METHOD_ARG_COUNT(c) if (lua_gettop(L) != c+1) { break; }
#define CHECK_METHOD_ARG(t, i) if (!LuaQt::ArgHelper<t>::CheckArg(L, i+1)) { break;}
#define GET_METHOD_ARG(t, i, n) t n = LuaQt::ArgHelper<t>::GetArg(L, i+1)

#define START_ARGREF_FRAME() LuaQt::StartArgRefFrame(L)
#define END_ARGREF_FRAME() LuaQt::EndArgRefFrame(L)
#define PUSH_RET_VAL(t, v) LuaQt::ArgHelper<t>::pushRetVal(L, v)
