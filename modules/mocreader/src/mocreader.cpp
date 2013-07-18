#include "mocreader.h"
#include <lua.hpp>

static int foo(lua_State *L)
{
	lua_pushliteral(L, "bar");
	return 1;
}

static luaL_Reg entries[] = {
	{"foo", foo},
};

inline void luaL_regfuncs(lua_State*L, luaL_Reg* reg, size_t count)
{
	for (size_t i =0; i < count; ++i)
	{
		lua_pushcfunction(L, reg[i].func);
		lua_setfield(L, -2, reg[i].name);
	}
}

#define luaL_newlib(l, m)  lua_createtable(l, 0, sizeof(m)/sizeof(m[0])); luaL_regfuncs(l, m, sizeof(m)/sizeof(m[0]))

extern "C" MOCREADER_EXPORT int luaopen_mocreader(lua_State *L)
{
	luaL_newlib(L, entries);
	return 1;
}
