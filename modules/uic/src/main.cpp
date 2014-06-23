/****************************************************************************
**
** Copyright (C) 2013 tdzl2003.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the tools applications of the LuaQt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "uic.h"
#include "option.h"
#include "driver.h"
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <lua.hpp>

static int run_cl(lua_State *L)
{
	Driver driver;

	driver.option().generator = Option::LuaGenerator;

	const char* fileName = luaL_checkstring(L, 1);
	QString inputFile = QString::fromUtf8(fileName);

	QByteArray ui_barray;
	QTextStream *ui_out = new QTextStream(&ui_barray);
	ui_out->setCodec(QTextCodec::codecForName("UTF-8"));

	QByteArray cl_barray;
	QTextStream *cl_out = new QTextStream(&cl_barray);
	cl_out->setCodec(QTextCodec::codecForName("UTF-8"));

	bool rtn = driver.uic(inputFile, ui_out , cl_out);
	delete ui_out;
	delete cl_out;
	if (!rtn) {
        return 0;
    }
	lua_pushlstring(L, cl_barray.data(), cl_barray.size());
	return 1;
}
static int run_ui(lua_State *L)
{
	Driver driver;

	driver.option().generator = Option::LuaGenerator;

	const char* fileName = luaL_checkstring(L, 1);
	QString inputFile = QString::fromUtf8(fileName);

	QByteArray ui_barray;
	QTextStream *ui_out = new QTextStream(&ui_barray);
	ui_out->setCodec(QTextCodec::codecForName("UTF-8"));

	QByteArray cl_barray;
	QTextStream *cl_out = new QTextStream(&cl_barray);
	cl_out->setCodec(QTextCodec::codecForName("UTF-8"));

	bool rtn = driver.uic(inputFile, ui_out , cl_out);
	delete ui_out;
	delete cl_out;
	if (!rtn) {
        return 0;
    }
	lua_pushlstring(L, ui_barray.data(), ui_barray.size());
	return 1;
}

static luaL_Reg entries[] = {
	//TODO: version number
	{"run_ui", run_ui},
	{"run_cl", run_cl},
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

extern "C" Q_DECL_EXPORT int luaopen_uic(lua_State *L)
{
	luaL_newlib(L, entries);
	return 1;
}

