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

#include <type_traits>

#include <QtCore/qcompilerdetection.h>

#include <lua.hpp>
#include <LuaQt/luaqt.hpp>

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
#define STR(x) #x

template<typename Enum>
class QFlags;

// Argument helper functions&macros
namespace LuaQt
{
	template <typename T>
	struct is_qobject_ptr
		: public std::tr1::false_type
	{
	};

	template <typename T>
	struct is_qobject_ptr<T*>
		: public std::tr1::is_base_of<QObject, T>
	{
	};

	template <typename T>
	class ArgHelperGeneral
	{
	public:
		static bool CheckArg(lua_State *L, int idx);
		static T GetArg(lua_State *L, int idx);
		static void pushRetVal(lua_State*L, const T& val);
		static void pushRetVal(lua_State*L, T&& val);
	};

	template <typename T>
	class ArgHelperEnum
	{
	public:
		static bool CheckArg(lua_State *L, int idx){
			return lua_isnumber(L, idx);;
		}
		static T GetArg(lua_State *L, int idx){
			return (T)(lua_tointeger(L, idx));
		}
		static void pushRetVal(lua_State*L, const T& val){
			lua_pushinteger(L, (int)val);
		}
		static void pushRetVal(lua_State*L, T&& val) {
			lua_pushinteger(L, (int)val);
		}
	};

	template <typename T>
	class ArgHelperQObjectPtr
	{
	public:
		static bool CheckArg(lua_State *L, int idx){
			luaL_error(L, "Not implemented.");
			return false;
		}
		static T GetArg(lua_State *L, int idx){
			luaL_error(L, "Not implemented.");
			return NULL;
		}
		static void pushRetVal(lua_State*L, const T& val){
			luaL_error(L, "Not implemented.");
			lua_pushnil(L);
		}
		static void pushRetVal(lua_State*L, T&& val) {
			luaL_error(L, "Not implemented.");
			lua_pushnil(L);
		}
	};

	template <typename T, 
		bool isEnum = std::tr1::is_enum<T>::value,
		bool isQObjectPtr = is_qobject_ptr<T>::value>
	class ArgHelper
		: public ArgHelperGeneral<T>
	{
	};

	template <typename T>
	class ArgHelper<T, true, false>
		: public ArgHelperEnum<T>
	{
	};

	template <typename T>
	class ArgHelper<QFlags<T>, false, false>
		: public ArgHelperEnum<QFlags<T>>
	{
	};

	template <typename T>
	class ArgHelper<T, false, true>
		: public ArgHelperQObjectPtr<T>
	{
	};

	using std::tr1::remove_reference;
}

#define CHECK_ARG_COUNT(c) if (lua_gettop(L) != c) { break; }
#define CHECK_ARG(t, i) if (!LuaQt::ArgHelper<LuaQt::remove_reference<t>::type>::CheckArg(L, i)) { break;}
#define GET_ARG(t, i, n) LuaQt::remove_reference<t>::type n = LuaQt::ArgHelper<LuaQt::remove_reference<t>::type>::GetArg(L, i)

#define CHECK_METHOD_ARG_COUNT(c) if (lua_gettop(L) != c+1) { break; }
#define CHECK_METHOD_ARG(t, i) if (!LuaQt::ArgHelper<LuaQt::remove_reference<t>::type>::CheckArg(L, i+1)) { break;}
#define GET_METHOD_ARG(t, i, n) LuaQt::remove_reference<t>::type n = LuaQt::ArgHelper<LuaQt::remove_reference<t>::type>::GetArg(L, i+1)

#define START_ARGREF_FRAME() LuaQt::StartArgRefFrame(L)
#define END_ARGREF_FRAME() LuaQt::EndArgRefFrame(L)
#define UNPACK_I(...) __VA_ARGS__
#define UNPACK__(p) UNPACK_I##p
#define UNPACK(P) UNPACK__(P)
#define PUSH_RET_VAL(t, v) LuaQt::ArgHelper<UNPACK(t)>::pushRetVal(L, v)

#include <LuaQT/fix.hpp>