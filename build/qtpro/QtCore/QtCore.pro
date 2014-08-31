#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T00:25:22
#
#-------------------------------------------------

QT       = core widgets

TARGET = QtCore
TEMPLATE = lib

#DEFINES += QTCORE_LIBRARY

SOURCES += \
    ../../../src/QtCore/signal.cpp 

include(../../../gen/QtCore/QtCore.pri)

INCLUDEPATH += ../../../include

win32:LIBS += lua51.lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += $$OUT_PWD/../LuaQt/release/LuaQt.lib
else:win32:CONFIG(debug, debug|release): LIBS += $$OUT_PWD/../LuaQt/debug/LuaQt.lib
else:unix: LIBS += -L$$OUT_PWD/../LuaQt/ -lLuaQt

