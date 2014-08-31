#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T00:25:22
#
#-------------------------------------------------

QT       = core gui widgets

TARGET = QtWidgets
TEMPLATE = lib

#DEFINES += QTCORE_LIBRARY

include(../../../gen/QtWidgets/QtWidgets.pri)

INCLUDEPATH += ../../../include

win32:LIBS += lua51.lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += $$OUT_PWD/../LuaQt/release/LuaQt.lib $$OUT_PWD/../QtCore/release/QtCore.lib $$OUT_PWD/../QtGui/release/QtGui.lib
else:win32:CONFIG(debug, debug|release): LIBS += $$OUT_PWD/../LuaQt/debug/LuaQt.lib $$OUT_PWD/../QtCore/debug/QtCore.lib $$OUT_PWD/../QtGui/debug/QtGui.lib
else:unix: LIBS += -L$$OUT_PWD/../LuaQt/ -lLuaQt

