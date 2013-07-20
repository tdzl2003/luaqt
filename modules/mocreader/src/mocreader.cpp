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

#include "mocreader.h"
#include <lua.hpp>
#include "preprocessor.h"
#include "moc.h"

#include <qfile.h>
#include <qfileinfo.h>
#include <qdir.h>

QByteArray composePreprocessorOutput(const Symbols &symbols);

Preprocessor initPreprocessor()
{
	Preprocessor pp;
	pp.macros["Q_MOC_RUN"];
    pp.macros["__cplusplus"];

	//TODO: define macros from parameters.

	Macro dummyVariadicFunctionMacro;
    dummyVariadicFunctionMacro.isFunction = true;
    dummyVariadicFunctionMacro.isVariadic = true;
    dummyVariadicFunctionMacro.arguments += Symbol(0, PP_IDENTIFIER, "__VA_ARGS__");

	pp.macros["__attribute__"] = dummyVariadicFunctionMacro;
	return pp;
}

void readPreprocessorParams(lua_State* L, int idx, Preprocessor& pp)
{
	//TODO: options:
	// prepend include files -b
	// force include -f
	// path prefix -p
	// Mac framework support

	lua_getfield(L, idx, "includePath");
	if (lua_istable(L, -1)){
		int len = lua_objlen(L, -1);
		for (int i = 0; i < len; ++i)
		{
			lua_rawgeti(L, -1, i+1);
			if (!lua_isstring(L, -1))
			{
				luaL_error(L, "includePath must be a table of string.");
			}
			pp.includes += Preprocessor::IncludePath(lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
}

static int mocreader_preprocess(lua_State *L)
{
	Preprocessor pp = initPreprocessor();
	pp.preprocessOnly = true;

	QByteArray filename = luaL_checkstring(L, 1);
    QByteArray output;
	FILE *in = 0;
    FILE *out = 0;

	// read options
	if (lua_istable(L, 2)){
		readPreprocessorParams(L, 2, pp);
	}

	in = fopen(filename.data(), "rb");
	if (!in) {
        luaL_error(L, "moc: %s: No such file\n", filename.constData());
    }

	Symbols sym = pp.preprocessed(filename, in);
	fclose(in);
	lua_pushstring(L, composePreprocessorOutput(sym).constData());

	return 1;
}

static int mocreader_parse(lua_State *L)
{
	Preprocessor pp = initPreprocessor();
	Moc moc;
	
	QByteArray filename = luaL_checkstring(L, 1);
    QByteArray output;
	FILE *in = 0;
    FILE *out = 0;

	//TODO: read options:
	// no warning
	// no noting
	if (lua_istable(L, 2)){
		readPreprocessorParams(L, 2, pp);
	}

	in = fopen(filename.data(), "rb");
	if (!in) {
        luaL_error(L, "moc: %s: No such file\n", filename.constData());
    }

	moc.currentFilenames.push(filename);
	moc.symbols = pp.preprocessed(moc.filename, in);
    fclose(in);
	
	moc.parse();
	
	return 0;
}

static luaL_Reg entries[] = {
	{"preprocess", mocreader_preprocess},
	{"parse", mocreader_parse},
	//TODO: version number
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

extern "C" MOCREADER_EXPORT int luaopen_mocreader(lua_State *L)
{
	luaL_newlib(L, entries);
	return 1;
}
