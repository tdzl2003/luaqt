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
#include <memory>

namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelper<int, false>;
	template class Q_DECL_EXPORT ArgHelper<unsigned int, false>;
	template class Q_DECL_EXPORT ArgHelper<void*, false>;
	template class Q_DECL_EXPORT ArgHelper<char**, false>;
	template class Q_DECL_EXPORT ArgHelper<QString, false>;

	Q_DECL_EXPORT bool ArgHelper<int, false>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT int ArgHelper<int, false>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelper<int, false>::pushRetVal(lua_State *L, const int& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelper<int, false>::pushRetVal(lua_State *L, int&& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT bool ArgHelper<unsigned int, false>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT unsigned int ArgHelper<unsigned int, false>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelper<unsigned int, false>::pushRetVal(lua_State *L, const unsigned int& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelper<unsigned int, false>::pushRetVal(lua_State *L, unsigned int&& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT bool ArgHelper<char**, false>::CheckArg(lua_State *L, int idx)
	{
		if (lua_istable(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT char** ArgHelper<char**, false>::GetArg(lua_State *L, int idx)
	{
		size_t count = lua_objlen(L, idx);
		char** out = (char**)allocArgRef(L, sizeof(char*)*(count+1));

		for (size_t i = 0; i < count; i++)
		{
			lua_rawgeti(L, idx, i+1);
			size_t len = 0;
			const char* data = lua_tolstring(L, -1, &len);
			char* dest = (char*)allocArgRef(L, len+1);
			memcpy(dest, data, len+1);
			out[i] = dest;
			lua_pop(L, 1);
		}
		out[count] = NULL;
		return out;
	}

	Q_DECL_EXPORT void ArgHelper<char**, false>::pushRetVal(lua_State *L, char** const& val)
	{
		luaL_error(L, "Not implemented: char** type as return value.");
	}

	Q_DECL_EXPORT void ArgHelper<char**, false>::pushRetVal(lua_State *L, char**&& val)
	{
		luaL_error(L, "Not implemented: char** type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelper<void*, false>::CheckArg(lua_State *L, int idx)
	{
		if (lua_islightuserdata(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT void* ArgHelper<void*, false>::GetArg(lua_State *L, int idx)
	{
		return lua_touserdata(L, idx);
	}

	Q_DECL_EXPORT void ArgHelper<void*, false>::pushRetVal(lua_State *L, void* const& val)
	{
		lua_pushlightuserdata(L, val);
	}

	Q_DECL_EXPORT void ArgHelper<void*, false>::pushRetVal(lua_State *L, void*&& val)
	{
		lua_pushlightuserdata(L, val);
	}

	Q_DECL_EXPORT bool ArgHelper<QString, false>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isstring(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT QString ArgHelper<QString, false>::GetArg(lua_State *L, int idx)
	{
		return QString::fromUtf8(lua_tostring(L, idx));
	}

	Q_DECL_EXPORT void ArgHelper<QString, false>::pushRetVal(lua_State *L, QString const& val)
	{
		lua_pushstring(L, val.toUtf8());
	}

	Q_DECL_EXPORT void ArgHelper<QString, false>::pushRetVal(lua_State *L, QString&& val)
	{
		lua_pushstring(L, val.toUtf8());
	}
}