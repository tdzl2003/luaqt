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
#include <LuaQt/callback.hpp>
#include <QtCore/QMetaType>
#include <QtCore/QObject>

#include <string>
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QMetaObject>

static int luaqt_getTypeId(lua_State *L)
{
	const char* tn = luaL_checkstring(L, 1);
	int ret = QMetaType::type(tn);
	if (ret >= QMetaType::FirstCoreType && ret <= QMetaType::HighestInternalId){
		lua_pushinteger(L, ret);
		return 1;
	}
	return 0;
}

static void null_qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
	
}

static int luaqt_defineMetaObject(lua_State *L)
{
	size_t strcount = 0;
	size_t totallen = 0;

	strcount = lua_objlen(L, 1);
	for (size_t i = 0; i < strcount; i++){
		lua_rawgeti(L, 1, i+1);
		totallen += lua_objlen(L, -1) +1;
		lua_pop(L, 1);
	}
	LuaQt::generic_callback* metaCall = new LuaQt::generic_callback(L);

	size_t datalen = lua_objlen(L, 2);
	char* data = (char*)lua_newuserdata(L, sizeof(QMetaObject) + sizeof(uint)*datalen + sizeof(QByteArrayData)*strcount + totallen );

	QMetaObject* obj = reinterpret_cast<QMetaObject*>(data);
	uint* metadata = reinterpret_cast<uint*>(data + sizeof(QMetaObject));
	QByteArrayData* stringdata = reinterpret_cast<QByteArrayData*>(data + sizeof(QMetaObject) + sizeof(uint)*datalen);
	char* strings = reinterpret_cast<char*>(data + sizeof(QMetaObject) + sizeof(uint)*datalen + sizeof(QByteArrayData)*strcount);

	{
		QMetaObject defineobj = {
			{
				reinterpret_cast<QMetaObject*>(lua_touserdata(L, 3)),
				stringdata, 
				metadata, 
				NULL,
				0,
				metaCall
			}
		};
		*obj = defineobj;
	}

	for (size_t i = 0; i < datalen; i++){
		lua_rawgeti(L, 2, i+1);
		metadata[i] = lua_tointeger(L, -1);
		lua_pop(L, 1);
	}

	{
		char* ptr = strings;
		for (size_t i = 0; i < strcount; i++){
			lua_rawgeti(L, 1, i+1);
			size_t len;
			const char* str = luaL_checklstring(L, -1, &len);
			memcpy(ptr, str, len);
			QByteArrayData tmp = {
					Q_REFCOUNT_INITIALIZE_STATIC, len, 0, 0, reinterpret_cast<char*>(ptr) - reinterpret_cast<char*>(stringdata+i)
			};
			stringdata[i] = tmp;
			ptr += len;
			*(ptr++) = 0;
			lua_pop(L, 1);
		}
	}
	

	return 1;
}

static int luaqt_activateSignal(lua_State *L)
{
	for (;;)
	{
		CHECK_ARG_COUNT(4);
		CHECK_ARG((QObject*), 1);
		CHECK_USERDATA_ARG(2);
		CHECK_ARG((int), 3);

		START_ARGREF_FRAME();
		GET_ARG((QObject*), 1, arg1);
		GET_USERDATA((const QMetaObject*), 2, arg2);
		GET_ARG((int), 3, arg3);

		void *_a[] = { 0 };
		QMetaObject::activate(arg1, arg2, arg3, _a);

		END_ARGREF_FRAME();
		return 0;
	}

	return luaL_error(L, "No valid overloads found");
}

static luaL_Reg luaqt_lib[] = {
	{"getTypeId", luaqt_getTypeId},
	{"defineMetaObject", luaqt_defineMetaObject},
	{"activate", luaqt_activateSignal},
	{NULL, NULL}
};

template <typename T>
struct General_argTranser{
    static int transer(lua_State *L)
    {
        void** a = (void**)lua_touserdata(L, 1);
        if (!a){
            return luaL_error(L, "Invalid argument.");
        }
        int i = luaL_checkint(L, 2);
        LuaQt::ArgHelper<T>::pushRetVal(L, *(reinterpret_cast<T*>(a[i])));
        return 1;
    }
};

#define GEN_TRANSTYPE(type) {#type, General_argTranser<type>::transer}

static luaL_Reg luaqt_argTranser[] = {
    GEN_TRANSTYPE(bool),
    GEN_TRANSTYPE(int),
    {NULL, NULL}
};

extern "C" Q_DECL_EXPORT int luaopen_LuaQt(lua_State*L)
{
	LuaQt::saveGlobalState(L);
	LuaQt::InitGCer(L);

	luaL_newlib(L, luaqt_lib);

    luaL_newlib(L, luaqt_argTranser);
    lua_setfield(L, -2, "pushArg");
	return 1;
}
