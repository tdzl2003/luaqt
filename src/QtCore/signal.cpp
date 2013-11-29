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

#include <QtCore/qobject.h>

int QObject_connect(lua_State *L)
{
	for (;;)
	{
		CHECK_ARG_COUNT(4);

		CHECK_ARG((QObject*), 1);
		CHECK_ARG((QObject*), 2);
		CHECK_ARG((const char*), 3);
		CHECK_ARG((const char*), 4);

		START_ARGREF_FRAME();
		GET_ARG((QObject*), 1, self);
		GET_ARG((QObject*), 2, sender);
		GET_ARG((const char*), 3, signal);
		GET_ARG((const char*), 4, slot);

		self->connect(sender, signal, slot);
		
		END_ARGREF_FRAME();

		return 0;
	}

	for (;;)
	{
		CHECK_ARG_COUNT(3);
		CHECK_ARG((QObject*), 1);
		CHECK_ARG((const char*), 2);
		CHECK_LUAFUNCTION_ARG(3);

		lua_pushvalue(L, 2);
		lua_gettable(L, 1);
		if (lua_isnil(L, -1))
		{
			GET_ARG((const char*), 2, signal);
			luaL_error(L, "Cannot find signal %s", signal);
			return 0;
		}
		lua_pushvalue(L, 1);
		lua_pushvalue(L, 3);
		lua_call(L, 2, 1);
		return 1;
	}

	return luaL_error(L, "No valid overload found.");
}