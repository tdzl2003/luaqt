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

static void lua_pushFunctionDef_Access(lua_State *L, FunctionDef::Access access)
{
	switch (access)
	{
	case FunctionDef::Private:
		lua_pushliteral(L, "private");
		break;
	case FunctionDef::Protected:
		lua_pushliteral(L, "protected");
		break;
	case FunctionDef::Public:
		lua_pushliteral(L, "public");
		break;
	default:
		lua_pushliteral(L, "unknown");
		break;
	}
}

static void lua_pushType_ReferenceType(lua_State *L, Type::ReferenceType reftype)
{
	switch (reftype)
	{
	case Type::NoReference:
		lua_pushliteral(L, "noreference");
		break;
	case Type::Reference:
		lua_pushliteral(L, "reference");
		break;
	case Type::RValueReference:
		lua_pushliteral(L, "rvalue");
		break;
	case Type::Pointer:
		lua_pushliteral(L, "pointer");
		break;
	default:
		lua_pushliteral(L, "unknown");
		break;
	}
}

static void lua_pushType(lua_State *L, const Type& type)
{
	lua_createtable(L, 0, 5);
	
	lua_pushstring(L, type.name);
	lua_setfield(L, -2, "name");
	
	lua_pushstring(L, type.rawName);
	lua_setfield(L, -2, "rawName");

	lua_pushboolean(L, type.isVolatile);
	lua_setfield(L, -2, "isVolatile");

	lua_pushboolean(L, type.isScoped);
	lua_setfield(L, -2, "isScoped");

	lua_pushType_ReferenceType(L, type.referenceType);
	lua_setfield(L, -2, "referenceType");
}

static void lua_pushArgumentDef(lua_State *L, const ArgumentDef& def)
{
	lua_createtable(L, 0, 6);

	lua_pushType(L, def.type);
	lua_setfield(L, -2, "type");

	lua_pushstring(L, def.rightType);
	lua_setfield(L, -2, "rightType");

	lua_pushstring(L, def.normalizedType);
	lua_setfield(L, -2, "normalizedType");

	lua_pushstring(L, def.name);
	lua_setfield(L, -2, "name");

	lua_pushstring(L, def.typeNameForCast);
	lua_setfield(L, -2, "typeNameForCast");

	lua_pushboolean(L, def.isDefault);
	lua_setfield(L, -2, "isDefault");
}

static void lua_pushFunctionDef(lua_State *L, const FunctionDef& def)
{
	lua_createtable(L, 0, 23);

	lua_pushType(L, def.type);
	lua_setfield(L, -2, "type");

	lua_pushstring(L, def.normalizedType);
	lua_setfield(L, -2, "normalizedType");

	lua_pushstring(L, def.tag);
	lua_setfield(L, -2, "tag");

	lua_pushstring(L, def.name);
	lua_setfield(L, -2, "name");

	lua_pushboolean(L, def.returnTypeIsVolatile);
	lua_setfield(L, -2, "returnTypeIsVolatile");

	lua_createtable(L, def.arguments.size(), 0);
	for (size_t i = 0; i < def.arguments.size(); ++i){
		lua_pushArgumentDef(L, def.arguments[i]);
		lua_rawseti(L, -2, i+1);
	}
	lua_setfield(L, -2, "arguments");

	lua_pushFunctionDef_Access(L, def.access);
	lua_setfield(L, -2, "access");

	lua_pushboolean(L, def.isConst);
	lua_setfield(L, -2, "isConst");

	lua_pushboolean(L, def.isVirtual);
	lua_setfield(L, -2, "isVirtual");

	lua_pushboolean(L, def.isStatic);
	lua_setfield(L, -2, "isStatic");

	lua_pushboolean(L, def.inlineCode);
	lua_setfield(L, -2, "inlineCode");

	lua_pushboolean(L, def.wasCloned);
	lua_setfield(L, -2, "wasCloned");

	lua_pushstring(L, def.inPrivateClass);
	lua_setfield(L, -2, "inPrivateClass");

	lua_pushboolean(L, def.isCompat);
	lua_setfield(L, -2, "isCompat");

	lua_pushboolean(L, def.isInvokable);
	lua_setfield(L, -2, "isInvokable");

	lua_pushboolean(L, def.isScriptable);
	lua_setfield(L, -2, "isScriptable");

	lua_pushboolean(L, def.isSlot);
	lua_setfield(L, -2, "isSlot");

	lua_pushboolean(L, def.isSignal);
	lua_setfield(L, -2, "isSignal");

	lua_pushboolean(L, def.isPrivateSignal);
	lua_setfield(L, -2, "isPrivateSignal");

	lua_pushboolean(L, def.isConstructor);
	lua_setfield(L, -2, "isConstructor");

	lua_pushboolean(L, def.isDestructor);
	lua_setfield(L, -2, "isDestructor");

	lua_pushboolean(L, def.isAbstract);
	lua_setfield(L, -2, "isAbstract");

	lua_pushinteger(L, def.revision);
	lua_setfield(L, -2, "revision");
}

static void lua_pushPropertyDef_Specification(lua_State *L, PropertyDef::Specification def)
{
	switch (def)
	{
	case PropertyDef::ValueSpec:
		lua_pushliteral(L, "valueSpec");
		break;
	case PropertyDef::ReferenceSpec:
		lua_pushliteral(L, "referenceSpec");
		break;
	case PropertyDef::PointerSpec:
		lua_pushliteral(L, "pointerSpec");
		break;
	default:
		lua_pushliteral(L, "unknown");
		break;
	}
}

static void lua_pushPropertyDef(lua_State *L, const PropertyDef& def)
{
	lua_createtable(L, 0, 18);

	lua_pushstring(L, def.name);
	lua_setfield(L, -2, "name");

	lua_pushstring(L, def.type);
	lua_setfield(L, -2, "type");

	lua_pushstring(L, def.member);
	lua_setfield(L, -2, "member");

	lua_pushstring(L, def.read);
	lua_setfield(L, -2, "read");

	lua_pushstring(L, def.write);
	lua_setfield(L, -2, "write");

	lua_pushstring(L, def.reset);
	lua_setfield(L, -2, "reset");

	lua_pushstring(L, def.designable);
	lua_setfield(L, -2, "designable");

	lua_pushstring(L, def.scriptable);
	lua_setfield(L, -2, "scriptable");

	lua_pushstring(L, def.editable);
	lua_setfield(L, -2, "editable");

	lua_pushstring(L, def.stored);
	lua_setfield(L, -2, "stored");

	lua_pushstring(L, def.user);
	lua_setfield(L, -2, "user");

	lua_pushstring(L, def.notify);
	lua_setfield(L, -2, "notify");

	lua_pushstring(L, def.inPrivateClass);
	lua_setfield(L, -2, "inPrivateClass");

	lua_pushnumber(L, def.notifyId);
	lua_setfield(L, -2, "notifyId");

	lua_pushboolean(L, def.constant);
	lua_setfield(L, -2, "constant");

	lua_pushboolean(L, def.final);
	lua_setfield(L, -2, "final");

	lua_pushPropertyDef_Specification(L, def.gspec);
	lua_setfield(L, -2, "gspec");

	lua_pushnumber(L, def.revision);
	lua_setfield(L, -2, "revision");
}

static void lua_pushClassInfoDef(lua_State *L, const ClassInfoDef& def)
{
	lua_createtable(L, 0, 2);

	lua_pushstring(L, def.name);
	lua_setfield(L, -2, "name");

	lua_pushstring(L, def.value);
	lua_setfield(L, -2, "value");
}

static void lua_pushEnumDef(lua_State *L, const EnumDef& def)
{
	lua_createtable(L, 0, 3);

	lua_pushstring(L, def.name);
	lua_setfield(L, -2, "name");

	// values
	lua_createtable(L, def.values.size(), 0);
	for (size_t i = 0; i < def.values.size(); ++i)
	{
		lua_pushstring(L, def.values[i]); 
		lua_rawseti(L, -2, i+1);
	}
	lua_setfield(L, -2, "values");

	lua_pushboolean(L, def.isEnumClass);
	lua_setfield(L, -2, "isEnumClass");
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

	lua_createtable(L, moc.classList.size(), 0);
	for (size_t i = 0; i < moc.classList.size(); ++i)
	{
		const ClassDef& def = moc.classList[i];
		lua_createtable(L, 0, 20);

		// classname
		lua_pushstring(L, def.classname.data());
		lua_setfield(L, -2, "classname");

		// qualified
		lua_pushstring(L, def.qualified.data());
		lua_setfield(L, -2, "qualified");

		// superclasses
		lua_createtable(L, def.superclassList.size(), 0);
		for (size_t j = 0; j < def.superclassList.size(); ++j)
		{
			lua_createtable(L, 0, 2);
			
			lua_pushstring(L, def.superclassList[j].first);
			lua_setfield(L, -2, "name");

			lua_pushFunctionDef_Access(L, def.superclassList[j].second);
			lua_setfield(L, -2, "access");

			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "superclassList");

		// interfaces
		// Don't know why interface list is a 2-dimensions list?
		lua_createtable(L, def.interfaceList.size(), 0);
		for (size_t j = 0; j < def.interfaceList.size(); ++j)
		{
			const QList<ClassDef::Interface>& list = def.interfaceList[j];
			lua_createtable(L, list.size(), 0);
			for (size_t k = 0; k < list.size(); ++k){
				lua_createtable(L, 0, 2);
				
				lua_pushstring(L, list[k].className);
				lua_setfield(L, -2, "className");

				lua_pushstring(L, list[k].interfaceId);
				lua_setfield(L, -2, "interfaceId");

				lua_rawseti(L, -2, k+1);
			}
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "interfaceList");

		// Don't know what does hasQObject&hasQGadget means, skipping.

		// pluginData
		lua_createtable(L, 0, 2);
		{
			lua_pushstring(L, def.pluginData.iid);
			lua_setfield(L, -2, "iid");

			lua_pushstring(L, def.pluginData.metaData.toJson());
			lua_setfield(L, -2, "metaData");
		}
		lua_setfield(L, -2, "pluginData");
		
		// constructorList
		lua_createtable(L, def.constructorList.size(), 0);
		for (size_t j = 0; j < def.constructorList.size(); ++j)
		{
			lua_pushFunctionDef(L, def.constructorList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "constructorList");

		// signalList
		lua_createtable(L, def.signalList.size(), 0);
		for (size_t j = 0; j < def.signalList.size(); ++j)
		{
			lua_pushFunctionDef(L, def.signalList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "signalList");

		// slotList
		lua_createtable(L, def.slotList.size(), 0);
		for (size_t j = 0; j < def.slotList.size(); ++j)
		{
			lua_pushFunctionDef(L, def.slotList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "slotList");

		// methodList
		lua_createtable(L, def.methodList.size(), 0);
		for (size_t j = 0; j < def.methodList.size(); ++j)
		{
			lua_pushFunctionDef(L, def.methodList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "methodList");

		// publicList
		lua_createtable(L, def.publicList.size(), 0);
		for (size_t j = 0; j < def.publicList.size(); ++j)
		{
			lua_pushFunctionDef(L, def.publicList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "publicList");

		// notifyableProperties
		lua_pushinteger(L, def.notifyableProperties);
		lua_setfield(L, -2, "notifyableProperties");

		// propertyList
		lua_createtable(L, def.propertyList.size(), 0);
		for (size_t j = 0; j < def.propertyList.size(); ++j)
		{
			lua_pushPropertyDef(L, def.propertyList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "propertyList");

		// classInfoList
		lua_createtable(L, def.classInfoList.size(), 0);
		for (size_t j = 0; j < def.classInfoList.size(); ++j)
		{
			lua_pushClassInfoDef(L, def.classInfoList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "classInfoList");

		//enumDeclarations
		lua_createtable(L, 0, def.enumDeclarations.size());
		for (QMap<QByteArray, bool>::const_iterator itor = def.enumDeclarations.begin();
			itor != def.enumDeclarations.end();
			++itor)
		{
			lua_pushboolean(L, itor.value());
			lua_setfield(L, -2, itor.key());
		}
		lua_setfield(L, -2, "enumDeclarations");

		// enumList
		lua_createtable(L, def.enumList.size(), 0);
		for (size_t j = 0; j < def.enumList.size(); ++j)
		{
			lua_pushEnumDef(L, def.enumList[j]);
			lua_rawseti(L, -2, j+1);
		}
		lua_setfield(L, -2, "enumList");

		//flagAliases
		lua_createtable(L, 0, def.flagAliases.size());
		for (QMap<QByteArray, QByteArray>::const_iterator itor = def.flagAliases.begin();
			itor != def.flagAliases.end();
			++itor)
		{
			lua_pushstring(L, itor.value());
			lua_setfield(L, -2, itor.key());
		}
		lua_setfield(L, -2, "flagAliases");

		lua_pushinteger(L, def.revisionedMethods);
		lua_setfield(L, -2, "revisionedMethods");

		lua_pushinteger(L, def.revisionedProperties);
		lua_setfield(L, -2, "revisionedProperties");

		lua_pushinteger(L, def.begin);
		lua_setfield(L, -2, "begin");

		lua_pushinteger(L, def.end);
		lua_setfield(L, -2, "end");

		lua_rawseti(L, -2, i+1);
	}
	
	return 1;
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
