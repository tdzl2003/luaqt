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

#ifdef LUA_QT_BUILD_CORE_LIB
#define LUA_QT_EXPORT Q_DECL_EXPORT
#else
#define LUA_QT_EXPORT Q_DECL_IMPORT
#endif

namespace LuaQt{
	LUA_QT_EXPORT void saveGlobalState(lua_State *L);
	LUA_QT_EXPORT lua_State* getGlobalState(lua_State *L);
}

// Weak ref functions
namespace LuaQt{
	LUA_QT_EXPORT int weakref(lua_State *L);
	LUA_QT_EXPORT void getweakref(lua_State *L, int id);
	LUA_QT_EXPORT void weakunref(lua_State *L, int id);
}

// Object life-cycle functions
class QObject;
namespace LuaQt{
	LUA_QT_EXPORT bool isObject(lua_State *L, int idx, const char* className);
	LUA_QT_EXPORT void* checkObject(lua_State *L, int idx, const char* className);

	LUA_QT_EXPORT void PushObject(lua_State *L, QObject* obj);
	LUA_QT_EXPORT void InitAndPushObject(lua_State *L, QObject* obj, void* ptr, const char* className);

	void LUA_QT_EXPORT InitGCer(lua_State *L);
}


// Meta functions:
namespace LuaQt{
	LUA_QT_EXPORT int General_index(lua_State *L);
	LUA_QT_EXPORT int General_newindex(lua_State *L);

	LUA_QT_EXPORT void StartArgRefFrame(lua_State *L);
	LUA_QT_EXPORT void EndArgRefFrame(lua_State *L);

	LUA_QT_EXPORT void* allocArgRef(lua_State *L, size_t size);
}
