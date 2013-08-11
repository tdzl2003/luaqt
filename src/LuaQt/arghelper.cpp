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
	bool ArgHelper<int>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	int ArgHelper<int>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	bool ArgHelper<char**>::CheckArg(lua_State *L, int idx)
	{
		if (lua_istable(L, idx))
		{
			return true;
		}
		return false;
	}

	char** ArgHelper<char**>::GetArg(lua_State *L, int idx)
	{
		size_t count = lua_objlen(L, idx);
		char** out = (char**)allocArgRef(L, sizeof(char*)*(count+1));

		for (size_t i = 0; i < count; i++)
		{
			lua_rawgeti(L, idx, i+1);
			size_t len = 0;
			const char* data = lua_tolstring(L, -1, &len);
			char* dest = (char*)allocArgRef(L, len);
			memcpy(dest, data, len);
			out[i] = dest;
			lua_pop(L, 1);
		}
		out[count] = NULL;
		return out;
	}


}