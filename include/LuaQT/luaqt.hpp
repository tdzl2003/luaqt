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
