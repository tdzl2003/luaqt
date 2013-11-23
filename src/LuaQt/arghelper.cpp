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
	template class Q_DECL_EXPORT ArgHelperGeneral<int>;
	template class Q_DECL_EXPORT ArgHelperGeneral<unsigned int>;
	template class Q_DECL_EXPORT ArgHelperGeneral<double>;

	Q_DECL_EXPORT bool ArgHelperGeneral<int>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT int ArgHelperGeneral<int>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<int>::pushRetVal(lua_State *L, const int& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<int>::pushRetVal(lua_State *L, int&& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<unsigned int>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT unsigned int ArgHelperGeneral<unsigned int>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<unsigned int>::pushRetVal(lua_State *L, const unsigned int& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<unsigned int>::pushRetVal(lua_State *L, unsigned int&& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<double>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT double ArgHelperGeneral<double>::GetArg(lua_State *L, int idx)
	{
		return lua_tonumber(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<double>::pushRetVal(lua_State *L, const double& idx)
	{
		lua_pushnumber(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<double>::pushRetVal(lua_State *L, double&& idx)
	{
		lua_pushnumber(L, idx);
	}
}

#include <QtCore/QStringList>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<char**>;
	template class Q_DECL_EXPORT ArgHelperGeneral<char const*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<void*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QString>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QStringList>;

	Q_DECL_EXPORT bool ArgHelperGeneral<char**>::CheckArg(lua_State *L, int idx)
	{
		if (lua_istable(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT char** ArgHelperGeneral<char**>::GetArg(lua_State *L, int idx)
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

	Q_DECL_EXPORT void ArgHelperGeneral<char**>::pushRetVal(lua_State *L, char** const& val)
	{
		luaL_error(L, "Not implemented: char** type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<char**>::pushRetVal(lua_State *L, char**&& val)
	{
		luaL_error(L, "Not implemented: char** type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<char const*>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isstring(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT char const* ArgHelperGeneral<char const*>::GetArg(lua_State *L, int idx)
	{
		return lua_tostring(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<char const*>::pushRetVal(lua_State *L, char const* const& val)
	{
		lua_pushstring(L, val);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<char const*>::pushRetVal(lua_State *L, char const*&& val)
	{
		lua_pushstring(L, val);
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<void*>::CheckArg(lua_State *L, int idx)
	{
		if (lua_islightuserdata(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT void* ArgHelperGeneral<void*>::GetArg(lua_State *L, int idx)
	{
		return lua_touserdata(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<void*>::pushRetVal(lua_State *L, void* const& val)
	{
		lua_pushlightuserdata(L, val);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<void*>::pushRetVal(lua_State *L, void*&& val)
	{
		lua_pushlightuserdata(L, val);
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QString>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isstring(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT QString ArgHelperGeneral<QString>::GetArg(lua_State *L, int idx)
	{
		return QString::fromUtf8(lua_tostring(L, idx));
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QString>::pushRetVal(lua_State *L, QString const& val)
	{
		lua_pushstring(L, val.toUtf8());
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QString>::pushRetVal(lua_State *L, QString&& val)
	{
		lua_pushstring(L, val.toUtf8());
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QStringList>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QStringList ArgHelperGeneral<QStringList>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStringList type as return value.");
		return QStringList();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStringList>::pushRetVal(lua_State *L, QStringList const& val)
	{
		luaL_error(L, "Not implemented: QStringList type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStringList>::pushRetVal(lua_State *L, QStringList&& val)
	{
		luaL_error(L, "Not implemented: QStringList type as return value.");
	}
}

#include <QtGui/QIcon>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QIcon>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QIcon>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QIcon ArgHelperGeneral<QIcon>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QIcon type as return value.");
		return QIcon();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QIcon>::pushRetVal(lua_State *L, QIcon const& val)
	{
		luaL_error(L, "Not implemented: QIcon type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QIcon>::pushRetVal(lua_State *L, QIcon&& val)
	{
		luaL_error(L, "Not implemented: QIcon type as return value.");
	}
}

#include <QtCore/QDateTime>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QDate>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QDateTime>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTime>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QDate>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QDate ArgHelperGeneral<QDate>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QDate type as return value.");
		return QDate();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QDate>::pushRetVal(lua_State *L, QDate const& val)
	{
		luaL_error(L, "Not implemented: QDate type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QDate>::pushRetVal(lua_State *L, QDate&& val)
	{
		luaL_error(L, "Not implemented: QDate type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QDateTime>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QDateTime ArgHelperGeneral<QDateTime>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QDateTime type as return value.");
		return QDateTime();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QDateTime>::pushRetVal(lua_State *L, QDateTime const& val)
	{
		luaL_error(L, "Not implemented: QDateTime type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QDateTime>::pushRetVal(lua_State *L, QDateTime&& val)
	{
		luaL_error(L, "Not implemented: QDateTime type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QTime>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QTime ArgHelperGeneral<QTime>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QTime type as return value.");
		return QTime();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QTime>::pushRetVal(lua_State *L, QTime const& val)
	{
		luaL_error(L, "Not implemented: QTime type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QTime>::pushRetVal(lua_State *L, QTime&& val)
	{
		luaL_error(L, "Not implemented: QTime type as return value.");
	}
}

#include <QtGui/QColor>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QColor>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QColor>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QColor ArgHelperGeneral<QColor>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QColor type as return value.");
		return QColor();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QColor>::pushRetVal(lua_State *L, QColor const& val)
	{
		luaL_error(L, "Not implemented: QColor type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QColor>::pushRetVal(lua_State *L, QColor&& val)
	{
		luaL_error(L, "Not implemented: QColor type as return value.");
	}
}


#include <QtGui/QFont>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QFont>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QFont>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QFont ArgHelperGeneral<QFont>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QFont type as return value.");
		return QFont();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFont>::pushRetVal(lua_State *L, QFont const& val)
	{
		luaL_error(L, "Not implemented: QFont type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFont>::pushRetVal(lua_State *L, QFont&& val)
	{
		luaL_error(L, "Not implemented: QFont type as return value.");
	}
}

#include <QtCore/QRectF>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QRectF>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QRectF>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QRectF ArgHelperGeneral<QRectF>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QRectF type as return value.");
		return QRectF();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QRectF>::pushRetVal(lua_State *L, QRectF const& val)
	{
		luaL_error(L, "Not implemented: QRectF type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QRectF>::pushRetVal(lua_State *L, QRectF&& val)
	{
		luaL_error(L, "Not implemented: QRectF type as return value.");
	}
}

#include <QtGui/QKeySequence>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QKeySequence>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QKeySequence>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QKeySequence ArgHelperGeneral<QKeySequence>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QKeySequence type as return value.");
		return QKeySequence();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QKeySequence>::pushRetVal(lua_State *L, QKeySequence const& val)
	{
		luaL_error(L, "Not implemented: QKeySequence type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QKeySequence>::pushRetVal(lua_State *L, QKeySequence&& val)
	{
		luaL_error(L, "Not implemented: QKeySequence type as return value.");
	}
}

#include <QtGui/QPixmap>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QPixmap>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QPixmap>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QPixmap ArgHelperGeneral<QPixmap>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QPixmap type as return value.");
		return QPixmap();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPixmap>::pushRetVal(lua_State *L, QPixmap const& val)
	{
		luaL_error(L, "Not implemented: QKeySequence type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPixmap>::pushRetVal(lua_State *L, QPixmap&& val)
	{
		luaL_error(L, "Not implemented: QKeySequence type as return value.");
	}
}

#include <QtWidgets\QGraphicsItem>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsItem*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QGraphicsItem*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QGraphicsItem* ArgHelperGeneral<QGraphicsItem*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QGraphicsItem* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QGraphicsItem*>::pushRetVal(lua_State *L, QGraphicsItem* const& val)
	{
		luaL_error(L, "Not implemented: QGraphicsItem* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QGraphicsItem*>::pushRetVal(lua_State *L, QGraphicsItem*&& val)
	{
		luaL_error(L, "Not implemented: QGraphicsItem* type as return value.");
	}
}