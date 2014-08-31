#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T00:25:22
#
#-------------------------------------------------

QT       = core gui

TARGET = QtGui
TEMPLATE = lib

#DEFINES += QTCORE_LIBRARY

include(../../../gen/QtGui/QtGui.pri)

INCLUDEPATH += ../../../include

win32:LIBS += lua51.lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += $$OUT_PWD/../LuaQt/release/LuaQt.lib $$OUT_PWD/../QtCore/release/QtCore.lib
else:win32:CONFIG(debug, debug|release): LIBS += $$OUT_PWD/../LuaQt/debug/LuaQt.lib $$OUT_PWD/../QtCore/debug/QtCore.lib
else:unix: LIBS += -L$$OUT_PWD/../LuaQt/ -lLuaQt

