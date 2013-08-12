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
#include <stdlib.h>

namespace LuaQt{
	void* allocObject(lua_State *L, size_t size, const char* className)
	{
		void* ret = malloc(size);

		lua_createtable(L, 0, 1);

		lua_pushlightuserdata(L, ret);
		lua_setfield(L, -2, className);

		luaL_getmetatable(L, className);
		lua_setmetatable(L, -2);

		return ret;
	}

	bool isObject(lua_State *L, int idx, const char* className)
	{
		lua_getfield(L, idx, className);
		bool ret = lua_islightuserdata(L, idx);
		lua_pop(L, 1);
		return ret;
	}

	void* checkObject(lua_State *L, int idx, const char* className)
	{
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

	void freeObject(lua_State *L, size_t size, int idx, const char* className)
	{
		void* obj = checkObject(L, idx, className);
		free(obj);
	}

}