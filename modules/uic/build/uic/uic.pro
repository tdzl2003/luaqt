#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T01:32:15
#
#-------------------------------------------------

QT       -= gui

TARGET = uic
TEMPLATE = lib

DEFINES += QT_UIC_LUA_GENERATOR

SOURCES += \
    ../../src/customwidgetsinfo.cpp \
    ../../src/databaseinfo.cpp \
    ../../src/driver.cpp \
    ../../src/main.cpp \
    ../../src/treewalker.cpp \
    ../../src/ui4.cpp \
    ../../src/uic.cpp \
    ../../src/validator.cpp \
    ../../src/lua/luawritedeclaration.cpp \
    ../../src/lua/luawriteincludes.cpp \
    ../../src/lua/luawriteinitialization.cpp

HEADERS += \
    ../../src/customwidgetsinfo.h \
    ../../src/databaseinfo.h \
    ../../src/driver.h \
    ../../src/globaldefs.h \
    ../../src/option.h \
    ../../src/qclass_lib_map.h \
    ../../src/treewalker.h \
    ../../src/ui4.h \
    ../../src/uic.h \
    ../../src/utils.h \
    ../../src/validator.h \
    ../../src/lua/luawritedeclaration.h \
    ../../src/lua/luawriteincludes.h \
    ../../src/lua/luawriteinitialization.h

LIBS += -llua51

unix {
    target.path = /usr/lib
    INSTALLS += target
}
