#-------------------------------------------------
#
# Project created by QtCreator 2014-07-17T23:56:23
#
#-------------------------------------------------

QT       += widgets

TARGET = LuaQt
TEMPLATE = lib

#DEFINES += LUAQT_LIBRARY

SOURCES +=  ../../../src/LuaQt/arghelper.cpp            \
            ../../../src/LuaQt/arghelper_nonimpl.cpp    \
            ../../../src/LuaQt/argrefframe.cpp          \
            ../../../src/LuaQt/globalstate.cpp          \
            ../../../src/LuaQt/luaqt.cpp                \
            ../../../src/LuaQt/metafunctions.cpp        \
            ../../../src/LuaQt/objectlifecycle.cpp      \
            ../../../src/LuaQt/weakref.cpp

INCLUDEPATH += ../../../include

win32:LIBS += lua51.lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
