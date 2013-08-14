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

namespace LuaQt{
	static int s_key_weaktable = 0;

	static void push_weaktable(lua_State *L)
	{
		lua_pushlightuserdata(L, &s_key_weaktable);
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);

			lua_createtable(L, 0, 0);

			lua_createtable(L, 0, 1);
			lua_pushliteral(L, "v");
			lua_setfield(L, -2, "__mode");

			lua_setmetatable(L, -2);

			lua_pushinteger(L, 3);
            lua_rawseti(L, -2, 1);
            
            lua_pushinteger(L, 0);
            lua_rawseti(L, -2, 2);

			lua_pushlightuserdata(L, &s_key_weaktable);
			lua_pushvalue(L, -2);
			lua_rawset(L, LUA_REGISTRYINDEX);
		}
	}

	#define length		1
	#define freelist	2

	static int wref(lua_State *L, int t)
    {
        int ref;
        if (lua_isnil(L, -1)) {
            lua_pop(L, 1);  /* remove from stack */
            return LUA_REFNIL;  /* `nil' has a unique fixed reference */
        }
        lua_rawgeti(L, t, freelist);  /* get first free element */
        ref = (int)lua_tointeger(L, -1);  /* ref = t[freelist] */
        lua_pop(L, 1);  /* remove it from stack */
        if (ref != 0) {  /* any free element? */
            lua_rawgeti(L, t, ref);  /* remove it from list */
            lua_rawseti(L, t, freelist);  /* (t[freelist] = t[ref]) */
        }
        else  /* no free elements */
        {
            lua_rawgeti(L, t, length);
            ref = (int)lua_tointeger(L, -1);
            lua_pop(L, 1);
            lua_pushinteger(L, ref+1);
            lua_rawseti(L, t, 1);
        }
        lua_rawseti(L, t, ref);
        return ref;
    }

	static void wunref (lua_State *L, int t, int ref) {
        //当使用lua_rawgeti时，栈里面已经为空
        if (ref >= 0) {
            lua_rawgeti(L, t, freelist);
            lua_rawseti(L, t, ref);  /* t[ref] = t[freelist] */
            lua_pushinteger(L, ref);
            lua_rawseti(L, t, freelist);  /* t[freelist] = ref */
        }
    }

	int weakref(lua_State *L)
	{
		push_weaktable(L);
		lua_insert(L, -2);
		int ret = wref(L, lua_gettop(L)-1);
        lua_pop(L, 1);
        return ret;
	}

	void getweakref(lua_State *L, int ref)
	{
		push_weaktable(L);
        lua_rawgeti(L, -1, ref);
        lua_remove(L, -2);

        //if (lua_isnil(L, -1))
        //{
        //    luaL_error(L, "Weak!");
        //}
	}

	void weakunref(lua_State *L, int ref)
	{
		if (ref > 0)
        {
            push_weaktable(L);
            wunref(L, lua_gettop(L)-1, ref);
            lua_pop(L, 1);
        }
	}

}
