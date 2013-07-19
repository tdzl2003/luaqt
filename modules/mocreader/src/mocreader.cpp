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

#include <qfile.h>
#include <qfileinfo.h>
#include <qdir.h>

static inline bool hasNext(const Symbols &symbols, int i)
{ return (i < symbols.size()); }

static inline const Symbol &next(const Symbols &symbols, int &i)
{ return symbols.at(i++); }

QByteArray composePreprocessorOutput(const Symbols &symbols) {
    QByteArray output;
    int lineNum = 1;
    Token last = PP_NOTOKEN;
    Token secondlast = last;
    int i = 0;
    while (hasNext(symbols, i)) {
        Symbol sym = next(symbols, i);
        switch (sym.token) {
        case PP_NEWLINE:
        case PP_WHITESPACE:
            if (last != PP_WHITESPACE) {
                secondlast = last;
                last = PP_WHITESPACE;
                output += ' ';
            }
            continue;
        case PP_STRING_LITERAL:
            if (last == PP_STRING_LITERAL)
                output.chop(1);
            else if (secondlast == PP_STRING_LITERAL && last == PP_WHITESPACE)
                output.chop(2);
            else
                break;
            output += sym.lexem().mid(1);
            secondlast = last;
            last = PP_STRING_LITERAL;
            continue;
        case MOC_INCLUDE_BEGIN:
            lineNum = 0;
            continue;
        case MOC_INCLUDE_END:
            lineNum = sym.lineNum;
            continue;
        default:
            break;
        }
        secondlast = last;
        last = sym.token;

        const int padding = sym.lineNum - lineNum;
        if (padding > 0) {
            output.resize(output.size() + padding);
            memset(output.data() + output.size() - padding, '\n', padding);
            lineNum = sym.lineNum;
        }

        output += sym.lexem();
    }

    return output;
}

static int mocreader_preprocess(lua_State *L)
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

	QByteArray filename = luaL_checkstring(L, 1);
    QByteArray output;
	FILE *in = 0;
    FILE *out = 0;

	bool autoInclude = true;
    bool defaultInclude = true;

	//TODO: options:
	// prepend include files -b
	// force include -f
	// path prefix -p
	// no warning
	// no noting
	// Mac framework support

	// parse args
	if (lua_istable(L, 2)){
		lua_getfield(L, 2, "includePath");
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

	in = fopen(filename.data(), "rb");
	if (!in) {
        luaL_error(L, "moc: %s: No such file\n", filename.constData());
    }

	pp.preprocessOnly = true;

	Symbols sym = pp.preprocessed(filename, in);
	lua_pushstring(L, composePreprocessorOutput(sym).constData());

	return 1;
}

static luaL_Reg entries[] = {
	{"preprocess", mocreader_preprocess},
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
