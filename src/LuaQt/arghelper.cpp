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
	template class Q_DECL_EXPORT ArgHelperGeneral<bool>;
	template class Q_DECL_EXPORT ArgHelperGeneral<int>;
	template class Q_DECL_EXPORT ArgHelperGeneral<unsigned int>;
	template class Q_DECL_EXPORT ArgHelperGeneral<unsigned long>;
	template class Q_DECL_EXPORT ArgHelperGeneral<__int64>;
    template class Q_DECL_EXPORT ArgHelperGeneral<unsigned __int64>;
	template class Q_DECL_EXPORT ArgHelperGeneral<long>;
	template class Q_DECL_EXPORT ArgHelperGeneral<double>;
	template class Q_DECL_EXPORT ArgHelperGeneral<double*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<bool>::CheckArg(lua_State *L, int idx)
	{
		return true;
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<bool>::GetArg(lua_State *L, int idx)
	{
		return lua_toboolean(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<bool>::pushRetVal(lua_State *L, const bool& idx)
	{
		lua_pushboolean(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<bool>::pushRetVal(lua_State *L, bool&& idx)
	{
		lua_pushboolean(L, idx);
	}

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

	Q_DECL_EXPORT bool ArgHelperGeneral<unsigned long>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT unsigned long ArgHelperGeneral<unsigned long>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<unsigned long>::pushRetVal(lua_State *L, const unsigned long& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<unsigned long>::pushRetVal(lua_State *L, unsigned long&& idx)
	{
		lua_pushinteger(L, idx);
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<__int64>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT __int64 ArgHelperGeneral<__int64>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<__int64>::pushRetVal(lua_State *L, const __int64& val)
	{
		lua_pushinteger(L, val);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<__int64>::pushRetVal(lua_State *L, __int64&& val)
	{
		lua_pushinteger(L, val);
	}

    Q_DECL_EXPORT bool ArgHelperGeneral<unsigned __int64>::CheckArg(lua_State *L, int idx)
    {
        if (lua_isnumber(L, idx))
        {
            return true;
        }
        return false;
    }

    Q_DECL_EXPORT unsigned __int64 ArgHelperGeneral<unsigned __int64>::GetArg(lua_State *L, int idx)
    {
        return lua_tointeger(L, idx);
    }

    Q_DECL_EXPORT void ArgHelperGeneral<unsigned __int64>::pushRetVal(lua_State *L, const unsigned __int64& val)
    {
        lua_pushinteger(L, val);
    }

    Q_DECL_EXPORT void ArgHelperGeneral<unsigned __int64>::pushRetVal(lua_State *L, unsigned __int64&& val)
    {
        lua_pushinteger(L, val);
    }

	Q_DECL_EXPORT bool ArgHelperGeneral<long>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isnumber(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT long ArgHelperGeneral<long>::GetArg(lua_State *L, int idx)
	{
		return lua_tointeger(L, idx);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<long>::pushRetVal(lua_State *L, const long& val)
	{
		lua_pushinteger(L, val);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<long>::pushRetVal(lua_State *L, long&& val)
	{
		lua_pushinteger(L, val);
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

	Q_DECL_EXPORT bool ArgHelperGeneral<double*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT double* ArgHelperGeneral<double*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: double* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<double*>::pushRetVal(lua_State *L, double* const& idx)
	{
		luaL_error(L, "Not implemented: double* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<double*>::pushRetVal(lua_State *L, double*&& idx)
	{
		luaL_error(L, "Not implemented: double* type as return value.");
	}
}

#include <QtCore/QUrl>
#include <QtCore/QStringList>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<char**>;
	template class Q_DECL_EXPORT ArgHelperGeneral<char const*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<void*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QByteArray>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QString>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QString*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QStringList>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QUrl>;

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

	Q_DECL_EXPORT bool ArgHelperGeneral<QByteArray>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isstring(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT QByteArray ArgHelperGeneral<QByteArray>::GetArg(lua_State *L, int idx)
	{
		size_t len;
		const char* data = lua_tolstring(L, idx, &len);
		return QByteArray(data, len);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QByteArray>::pushRetVal(lua_State *L, QByteArray const& val)
	{
		lua_pushlstring(L, val.data(), val.length());
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QByteArray>::pushRetVal(lua_State *L, QByteArray&& val)
	{
		lua_pushlstring(L, val.data(), val.length());
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
		size_t len;
		const char* data = lua_tolstring(L, idx, &len);
		return QString::fromUtf8(data, len);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QString>::pushRetVal(lua_State *L, QString const& val)
	{
		QByteArray data = val.toUtf8();
		lua_pushlstring(L, data.data(), data.length());
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QString>::pushRetVal(lua_State *L, QString&& val)
	{
		QByteArray data = val.toUtf8();
		lua_pushlstring(L, data.data(), data.length());
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QUrl>::CheckArg(lua_State *L, int idx)
	{
		if (lua_isstring(L, idx))
		{
			return true;
		}
		return false;
	}

	Q_DECL_EXPORT QUrl ArgHelperGeneral<QUrl>::GetArg(lua_State *L, int idx)
	{
		size_t len;
		const char* data = lua_tolstring(L, idx, &len);
		return QUrl(QString::fromUtf8(data, len));
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QUrl>::pushRetVal(lua_State *L, QUrl const& val)
	{
		QByteArray data = val.url().toUtf8();
		lua_pushlstring(L, data.data(), data.length());
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QUrl>::pushRetVal(lua_State *L, QUrl&& val)
	{
		QByteArray data = val.url().toUtf8();
		lua_pushlstring(L, data.data(), data.length());
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QString*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QString* ArgHelperGeneral<QString*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QString* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QString*>::pushRetVal(lua_State *L, QString* const& idx)
	{
		luaL_error(L, "Not implemented: QString* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QString*>::pushRetVal(lua_State *L, QString*&& idx)
	{
		luaL_error(L, "Not implemented: QString* type as return value.");
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
#include <QtGui/QFontInfo>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QFont>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QFontInfo>;

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

	Q_DECL_EXPORT bool ArgHelperGeneral<QFontInfo>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QFontInfo ArgHelperGeneral<QFontInfo>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QFontInfo type as return value.");
		return QFontInfo(QFont());
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFontInfo>::pushRetVal(lua_State *L, QFontInfo const& val)
	{
		luaL_error(L, "Not implemented: QFontInfo type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFontInfo>::pushRetVal(lua_State *L, QFontInfo&& val)
	{
		luaL_error(L, "Not implemented: QFontInfo type as return value.");
	}
}

#include <QtCore/QRect>
#include <QtCore/QRectF>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QRect>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QRectF>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QRect>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QRect ArgHelperGeneral<QRect>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QRect type as return value.");
		return QRect();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QRect>::pushRetVal(lua_State *L, QRect const& val)
	{
		luaL_error(L, "Not implemented: QRect type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QRect>::pushRetVal(lua_State *L, QRect&& val)
	{
		luaL_error(L, "Not implemented: QRect type as return value.");
	}

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

#include <QtCore/QSize>
#include <QtCore/QSizeF>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QSize>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QSizeF>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPoint>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPointF>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QPoint>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QPoint ArgHelperGeneral<QPoint>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QPoint type as return value.");
		return QPoint();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPoint>::pushRetVal(lua_State *L, QPoint const& val)
	{
		luaL_error(L, "Not implemented: QPoint type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPoint>::pushRetVal(lua_State *L, QPoint&& val)
	{
		luaL_error(L, "Not implemented: QPoint type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QPointF>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QPointF ArgHelperGeneral<QPointF>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QPointF type as return value.");
		return QPointF();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPointF>::pushRetVal(lua_State *L, QPointF const& val)
	{
		luaL_error(L, "Not implemented: QPointF type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPointF>::pushRetVal(lua_State *L, QPointF&& val)
	{
		luaL_error(L, "Not implemented: QPoint type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QSize>::CheckArg(lua_State *L, int idx)
	{
        if (lua_istable(L, idx)){
            return true;
        }
        return false;
	}

	Q_DECL_EXPORT QSize ArgHelperGeneral<QSize>::GetArg(lua_State *L, int idx)
	{
        if (lua_istable(L, idx)){
            int w = 0, h = 0;
            lua_rawgeti(L, idx, 1);
            w = lua_tointeger(L, -1);
            lua_pop(L, 1);
            lua_rawgeti(L, idx, 2);
            h = lua_tointeger(L, -1);
            lua_pop(L, 1);
            return QSize(w, h);

        }
		return QSize();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QSize>::pushRetVal(lua_State *L, QSize const& val)
	{
        lua_createtable(L, 2, 0);
        lua_pushinteger(L, val.width());
        lua_rawseti(L, -2, 1);
        lua_pushinteger(L, val.height());
        lua_rawseti(L, -2, 2);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QSize>::pushRetVal(lua_State *L, QSize&& val)
	{
        lua_createtable(L, 2, 0);
        lua_pushinteger(L, val.width());
        lua_rawseti(L, -2, 1);
        lua_pushinteger(L, val.height());
        lua_rawseti(L, -2, 2);
    }

	Q_DECL_EXPORT bool ArgHelperGeneral<QSizeF>::CheckArg(lua_State *L, int idx)
	{
        if (lua_istable(L, idx)){
            return true;
        }
        return false;
	}

	Q_DECL_EXPORT QSizeF ArgHelperGeneral<QSizeF>::GetArg(lua_State *L, int idx)
	{
        if (lua_istable(L, idx)){
            qreal w = 0, h = 0;
            lua_rawgeti(L, idx, 1);
            w = lua_tonumber(L, -1);
            lua_pop(L, 1);
            lua_rawgeti(L, idx, 2);
            h = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return QSizeF(w, h);

        }
        return QSizeF();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QSizeF>::pushRetVal(lua_State *L, QSizeF const& val)
	{
        lua_createtable(L, 2, 0);
        lua_pushnumber(L, val.width());
        lua_rawseti(L, -2, 1);
        lua_pushnumber(L, val.height());
        lua_rawseti(L, -2, 2);
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QSizeF>::pushRetVal(lua_State *L, QSizeF&& val)
	{
        lua_createtable(L, 2, 0);
        lua_pushnumber(L, val.width());
        lua_rawseti(L, -2, 1);
        lua_pushnumber(L, val.height());
        lua_rawseti(L, -2, 2);
	}
}

#include <QtCore/QModelIndex>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QModelIndex>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QModelIndex>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QModelIndex ArgHelperGeneral<QModelIndex>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QModelIndex type as return value.");
		return QModelIndex();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QModelIndex>::pushRetVal(lua_State *L, QModelIndex const& val)
	{
		luaL_error(L, "Not implemented: QModelIndex type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QModelIndex>::pushRetVal(lua_State *L, QModelIndex&& val)
	{
		luaL_error(L, "Not implemented: QModelIndex type as return value.");
	}
}

#include <QtWidgets/QStyleOptionViewItem>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QStyleOptionViewItem>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QStyleOptionViewItem>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QStyleOptionViewItem ArgHelperGeneral<QStyleOptionViewItem>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStyleOptionViewItem type as return value.");
		return QStyleOptionViewItem();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleOptionViewItem>::pushRetVal(lua_State *L, QStyleOptionViewItem const& val)
	{
		luaL_error(L, "Not implemented: QStyleOptionViewItem type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleOptionViewItem>::pushRetVal(lua_State *L, QStyleOptionViewItem&& val)
	{
		luaL_error(L, "Not implemented: QStyleOptionViewItem type as return value.");
	}
}


#include <QtCore/QEvent>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QEvent*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QEvent*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QEvent* ArgHelperGeneral<QEvent*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStyleOptionViewItem type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QEvent*>::pushRetVal(lua_State *L, QEvent* const& val)
	{
		luaL_error(L, "Not implemented: QEvent* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QEvent*>::pushRetVal(lua_State *L, QEvent*&& val)
	{
		luaL_error(L, "Not implemented: QEvent* type as return value.");
	}
}


#include <QtGui/QHelpEvent>
namespace LuaQt
{
	template class Q_DECL_EXPORT ArgHelperGeneral<QHelpEvent*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QHelpEvent*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QHelpEvent* ArgHelperGeneral<QHelpEvent*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStyleOptionViewItem type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QHelpEvent*>::pushRetVal(lua_State *L, QHelpEvent* const& val)
	{
		luaL_error(L, "Not implemented: QEvent* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QHelpEvent*>::pushRetVal(lua_State *L, QHelpEvent*&& val)
	{
		luaL_error(L, "Not implemented: QEvent* type as return value.");
	}
}

#include <QtGui/QFontMetrics>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QFontMetrics>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QFontMetrics>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QFontMetrics ArgHelperGeneral<QFontMetrics>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QFontMetrics type as return value.");
		return QFontMetrics(QFont());
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFontMetrics>::pushRetVal(lua_State *L, QFontMetrics const& val)
	{
		luaL_error(L, "Not implemented: QFontMetrics type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFontMetrics>::pushRetVal(lua_State *L, QFontMetrics&& val)
	{
		luaL_error(L, "Not implemented: QFontMetrics type as return value.");
	}
}

#include <QtGui/QPainter>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QPainter*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QPainter*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QPainter* ArgHelperGeneral<QPainter*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QPainter* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPainter*>::pushRetVal(lua_State *L, QPainter* const& val)
	{
		luaL_error(L, "Not implemented: QPainter* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPainter*>::pushRetVal(lua_State *L, QPainter*&& val)
	{
		luaL_error(L, "Not implemented: QPainter* type as return value.");
	}
}

#include <QtCore/QVariant>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QVariant>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QVariant>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QVariant ArgHelperGeneral<QVariant>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QVariant type as return value.");
		return QVariant();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QVariant>::pushRetVal(lua_State *L, QVariant const& val)
	{
		luaL_error(L, "Not implemented: QVariant type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QVariant>::pushRetVal(lua_State *L, QVariant&& val)
	{
		luaL_error(L, "Not implemented: QVariant type as return value.");
	}
}

#include <QtGui/QPalette>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QPalette>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QPalette>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QPalette ArgHelperGeneral<QPalette>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QPalette type as return value.");
		return QPalette();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPalette>::pushRetVal(lua_State *L, QPalette const& val)
	{
		luaL_error(L, "Not implemented: QPalette type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QPalette>::pushRetVal(lua_State *L, QPalette&& val)
	{
		luaL_error(L, "Not implemented: QPalette type as return value.");
	}
}

#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QLayoutItem>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QSpacerItem*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QLayoutItem*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QSpacerItem*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QSpacerItem* ArgHelperGeneral<QSpacerItem*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QSpacerItem* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QSpacerItem*>::pushRetVal(lua_State *L, QSpacerItem* const& val)
	{
		luaL_error(L, "Not implemented: QSpacerItem* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QSpacerItem*>::pushRetVal(lua_State *L, QSpacerItem*&& val)
	{
		luaL_error(L, "Not implemented: QSpacerItem* type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QLayoutItem*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QLayoutItem* ArgHelperGeneral<QLayoutItem*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QLayoutItem* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QLayoutItem*>::pushRetVal(lua_State *L, QLayoutItem* const& val)
	{
		luaL_error(L, "Not implemented: QLayoutItem* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QLayoutItem*>::pushRetVal(lua_State *L, QLayoutItem*&& val)
	{
		luaL_error(L, "Not implemented: QLayoutItem* type as return value.");
	}
}

#include <QtGui/QTextCharFormat>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextCharFormat>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QTextCharFormat>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QTextCharFormat ArgHelperGeneral<QTextCharFormat>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QTextCharFormat type as return value.");
		return QTextCharFormat();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QTextCharFormat>::pushRetVal(lua_State *L, QTextCharFormat const& val)
	{
		luaL_error(L, "Not implemented: QTextCharFormat type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QTextCharFormat>::pushRetVal(lua_State *L, QTextCharFormat&& val)
	{
		luaL_error(L, "Not implemented: QTextCharFormat type as return value.");
	}
}

#include <QtWidgets/QStyleOptionComplex>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QStyleOptionComplex const *>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QStyleOptionComplex const *>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QStyleOptionComplex const * ArgHelperGeneral<QStyleOptionComplex const *>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStyleOptionComplex const * type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleOptionComplex const *>::pushRetVal(lua_State *L, QStyleOptionComplex const * const& val)
	{
		luaL_error(L, "Not implemented: QStyleOptionComplex const * type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleOptionComplex const *>::pushRetVal(lua_State *L, QStyleOptionComplex const *&& val)
	{
		luaL_error(L, "Not implemented: QStyleOptionComplex const * type as return value.");
	}
}


#include <QtWidgets/QStyleOption>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QStyleOption const *>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QStyleOption const *>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QStyleOption const * ArgHelperGeneral<QStyleOption const *>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStyleOption const * type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleOption const *>::pushRetVal(lua_State *L, QStyleOption const * const& val)
	{
		luaL_error(L, "Not implemented: QStyleOption const * type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleOption const *>::pushRetVal(lua_State *L, QStyleOption const *&& val)
	{
		luaL_error(L, "Not implemented: QStyleOption const * type as return value.");
	}
}

#include <QtWidgets/QStyleHintReturn>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QStyleHintReturn*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QStyleHintReturn*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QStyleHintReturn* ArgHelperGeneral<QStyleHintReturn*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QStyleHintReturn* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleHintReturn*>::pushRetVal(lua_State *L, QStyleHintReturn* const& val)
	{
		luaL_error(L, "Not implemented: QStyleHintReturn* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QStyleHintReturn*>::pushRetVal(lua_State *L, QStyleHintReturn*&& val)
	{
		luaL_error(L, "Not implemented: QStyleHintReturn* type as return value.");
	}
}

#include <QtCore/QFileInfo>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QFileInfo>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QFileInfo>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QFileInfo ArgHelperGeneral<QFileInfo>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QFileInfo type as return value.");
		return QFileInfo();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFileInfo>::pushRetVal(lua_State *L, QFileInfo const& val)
	{
		luaL_error(L, "Not implemented: QFileInfo type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFileInfo>::pushRetVal(lua_State *L, QFileInfo&& val)
	{
		luaL_error(L, "Not implemented: QFileInfo type as return value.");
	}
}

#include <QtWidgets/QFileIconProvider>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QFileIconProvider*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QFileIconProvider*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QFileIconProvider* ArgHelperGeneral<QFileIconProvider*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QFileIconProvider* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFileIconProvider*>::pushRetVal(lua_State *L, QFileIconProvider* const& val)
	{
		luaL_error(L, "Not implemented: QFileIconProvider* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QFileIconProvider*>::pushRetVal(lua_State *L, QFileIconProvider*&& val)
	{
		luaL_error(L, "Not implemented: QFileIconProvider* type as return value.");
	}
}

#include <QtCore/QDir>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QDir>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QDir>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QDir ArgHelperGeneral<QDir>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QDir type as return value.");
		return QDir();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QDir>::pushRetVal(lua_State *L, QDir const& val)
	{
		luaL_error(L, "Not implemented: QDir type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QDir>::pushRetVal(lua_State *L, QDir&& val)
	{
		luaL_error(L, "Not implemented: QDir type as return value.");
	}
}

#include <QtWidgets\qgraphicseffect.h>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsEffectSource*>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QGraphicsEffectSource*>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QGraphicsEffectSource* ArgHelperGeneral<QGraphicsEffectSource*>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QGraphicsEffectSource* type as return value.");
		return NULL;
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QGraphicsEffectSource*>::pushRetVal(lua_State *L, QGraphicsEffectSource* const& val)
	{
		luaL_error(L, "Not implemented: QGraphicsEffectSource* type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QGraphicsEffectSource*>::pushRetVal(lua_State *L, QGraphicsEffectSource*&& val)
	{
		luaL_error(L, "Not implemented: QGraphicsEffectSource* type as return value.");
	}
}

#include <QtGui/QMatrix>
#include <QtGui/QMatrix4x4>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QVector3D>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QMatrix>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QMatrix4x4>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QVector3D>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QVector3D ArgHelperGeneral<QVector3D>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QVector3D type as return value.");
		return QVector3D();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QVector3D>::pushRetVal(lua_State *L, QVector3D const& val)
	{
		luaL_error(L, "Not implemented: QVector3D type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QVector3D>::pushRetVal(lua_State *L, QVector3D&& val)
	{
		luaL_error(L, "Not implemented: QVector3D type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QMatrix>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QMatrix ArgHelperGeneral<QMatrix>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QMatrix type as return value.");
		return QMatrix();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QMatrix>::pushRetVal(lua_State *L, QMatrix const& val)
	{
		luaL_error(L, "Not implemented: QMatrix type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QMatrix>::pushRetVal(lua_State *L, QMatrix&& val)
	{
		luaL_error(L, "Not implemented: QMatrix type as return value.");
	}

	Q_DECL_EXPORT bool ArgHelperGeneral<QMatrix4x4>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QMatrix4x4 ArgHelperGeneral<QMatrix4x4>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QMatrix4x4 type as return value.");
		return QMatrix4x4();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QMatrix4x4>::pushRetVal(lua_State *L, QMatrix4x4 const& val)
	{
		luaL_error(L, "Not implemented: QMatrix4x4 type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QMatrix4x4>::pushRetVal(lua_State *L, QMatrix4x4&& val)
	{
		luaL_error(L, "Not implemented: QMaQMatrix4x4trix type as return value.");
	}
}

#include <QtGui/QBrush>
namespace LuaQt{
	template class Q_DECL_EXPORT ArgHelperGeneral<QBrush>;

	Q_DECL_EXPORT bool ArgHelperGeneral<QBrush>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	Q_DECL_EXPORT QBrush ArgHelperGeneral<QBrush>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented: QBrush type as return value.");
		return QBrush();
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QBrush>::pushRetVal(lua_State *L, QBrush const& val)
	{
		luaL_error(L, "Not implemented: QBrush type as return value.");
	}

	Q_DECL_EXPORT void ArgHelperGeneral<QBrush>::pushRetVal(lua_State *L, QBrush&& val)
	{
		luaL_error(L, "Not implemented: QBrush type as return value.");
	}
}

