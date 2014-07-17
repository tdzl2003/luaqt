#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T00:25:22
#
#-------------------------------------------------

QT       = core gui

TARGET = QtGui
TEMPLATE = lib

#DEFINES += QTCORE_LIBRARY

SOURCES += \ 
    ../../../gen/QtGui/defQAbstractTextDocumentLayout.cpp \
    ../../../gen/QtGui/defQAccessibleBridgePlugin.cpp \
    ../../../gen/QtGui/defQAccessiblePlugin.cpp \
    ../../../gen/QtGui/defQClipboard.cpp \
    ../../../gen/QtGui/defQDoubleValidator.cpp \
    ../../../gen/QtGui/defQDrag.cpp \
    ../../../gen/QtGui/defQGenericPlugin.cpp \
    ../../../gen/QtGui/defQGuiApplication.cpp \
    ../../../gen/QtGui/defQIconEnginePlugin.cpp \
    ../../../gen/QtGui/defQImageIOPlugin.cpp \
    ../../../gen/QtGui/defQInputMethod.cpp \
    ../../../gen/QtGui/defQIntValidator.cpp \
    ../../../gen/QtGui/defQMovie.cpp \
    ../../../gen/QtGui/defQOffscreenSurface.cpp \
    ../../../gen/QtGui/defQOpenGLTimeMonitor.cpp \
    ../../../gen/QtGui/defQOpenGLTimerQuery.cpp \
    ../../../gen/QtGui/defQPictureFormatPlugin.cpp \
    ../../../gen/QtGui/defQRegExpValidator.cpp \
    ../../../gen/QtGui/defQRegularExpressionValidator.cpp \
    ../../../gen/QtGui/defQScreen.cpp \
    ../../../gen/QtGui/defQSessionManager.cpp \
    ../../../gen/QtGui/defQStandardItemModel.cpp \
    ../../../gen/QtGui/defQStyleHints.cpp \
    ../../../gen/QtGui/defQSyntaxHighlighter.cpp \
    ../../../gen/QtGui/defQTextBlockGroup.cpp \
    ../../../gen/QtGui/defQTextDocument.cpp \
    ../../../gen/QtGui/defQTextFrame.cpp \
    ../../../gen/QtGui/defQTextList.cpp \
    ../../../gen/QtGui/defQTextObject.cpp \
    ../../../gen/QtGui/defQTextTable.cpp \
    ../../../gen/QtGui/defQValidator.cpp \
    ../../../gen/QtGui/defQWindow.cpp \
    ../../../gen/QtGui/QtGui.cpp

INCLUDEPATH += ../../../include

win32:LIBS += lua51.lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += $$OUT_PWD/../LuaQt/release/LuaQt.lib $$OUT_PWD/../QtCore/release/QtCore.lib
else:win32:CONFIG(debug, debug|release): LIBS += $$OUT_PWD/../LuaQt/debug/LuaQt.lib $$OUT_PWD/../QtCore/debug/QtCore.lib
else:unix: LIBS += -L$$OUT_PWD/../LuaQt/ -lLuaQt

