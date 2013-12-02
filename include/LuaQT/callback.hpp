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
#include <LuaQT/luaqt.hpp>

namespace LuaQt
{
	class generic_callback
	{
	public:
		generic_callback(lua_State *_L)
		{
			L = getGlobalState(_L);
			ref = lua_ref(L, true);
		}
		~generic_callback()
		{
			if (ref != LUA_REFNIL && ref != LUA_NOREF) {
				lua_unref(L, true);
			}
		}
		generic_callback(generic_callback&& other){
			L = other.L;
			ref = other.ref;
			other.ref = LUA_REFNIL;
		}
		void operator = (generic_callback&& other){
			L = other.L;
			ref = other.ref;
			other.ref = LUA_REFNIL;
		}
		generic_callback(const generic_callback& other)
		{
			L = other.L;
			lua_getref(L, other.ref);
			ref = lua_ref(L, true);
		}
		void operator = (const generic_callback& other)
		{
			L = other.L;
			lua_getref(L, other.ref);
			ref = lua_ref(L, true);
		}
		void push()
		{
			lua_getref(L, ref);
		}

		lua_State *getState()
		{
			return L;
		}

	protected:
		lua_State *L;
		int ref;
	private:
		
	};
}