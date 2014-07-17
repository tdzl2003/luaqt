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
    ../../../src/QtCore/signal.cpp \
    ../../../gen/QtCore/defQAbstractAnimation.cpp \
    ../../../gen/QtCore/defQAbstractEventDispatcher.cpp \
    ../../../gen/QtCore/defQAbstractItemModel.cpp \
    ../../../gen/QtCore/defQAbstractListModel.cpp \
    ../../../gen/QtCore/defQAbstractProxyModel.cpp \
    ../../../gen/QtCore/defQAbstractState.cpp \
    ../../../gen/QtCore/defQAbstractTableModel.cpp \
    ../../../gen/QtCore/defQAbstractTransition.cpp \
    ../../../gen/QtCore/defQAnimationDriver.cpp \
    ../../../gen/QtCore/defQAnimationGroup.cpp \
    ../../../gen/QtCore/defQBuffer.cpp \
    ../../../gen/QtCore/defQCoreApplication.cpp \
    ../../../gen/QtCore/defQEventLoop.cpp \
    ../../../gen/QtCore/defQEventTransition.cpp \
    ../../../gen/QtCore/defQFileDevice.cpp \
    ../../../gen/QtCore/defQFileSelector.cpp \
    ../../../gen/QtCore/defQFileSystemWatcher.cpp \
    ../../../gen/QtCore/defQFinalState.cpp \
    ../../../gen/QtCore/defQFutureWatcherBase.cpp \
    ../../../gen/QtCore/defQHistoryState.cpp \
    ../../../gen/QtCore/defQIdentityProxyModel.cpp \
    ../../../gen/QtCore/defQIODevice.cpp \
    ../../../gen/QtCore/defQItemSelectionModel.cpp \
    ../../../gen/QtCore/defQLibrary.cpp \
    ../../../gen/QtCore/defQMimeData.cpp \
    ../../../gen/QtCore/defQObject.cpp \
    ../../../gen/QtCore/defQObjectCleanupHandler.cpp \
    ../../../gen/QtCore/defQParallelAnimationGroup.cpp \
    ../../../gen/QtCore/defQPauseAnimation.cpp \
    ../../../gen/QtCore/defQPluginLoader.cpp \
    ../../../gen/QtCore/defQSaveFile.cpp \
    ../../../gen/QtCore/defQSequentialAnimationGroup.cpp \
    ../../../gen/QtCore/defQSharedMemory.cpp \
    ../../../gen/QtCore/defQSignalMapper.cpp \
    ../../../gen/QtCore/defQSignalTransition.cpp \
    ../../../gen/QtCore/defQSocketNotifier.cpp \
    ../../../gen/QtCore/defQSortFilterProxyModel.cpp \
    ../../../gen/QtCore/defQState.cpp \
    ../../../gen/QtCore/defQStateMachine.cpp \
    ../../../gen/QtCore/defQStringListModel.cpp \
    ../../../gen/QtCore/defQTimeLine.cpp \
    ../../../gen/QtCore/defQTimer.cpp \
    ../../../gen/QtCore/defQTranslator.cpp \
    ../../../gen/QtCore/QtCore.cpp

INCLUDEPATH += ../../../include

win32:LIBS += lua51.lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += $$OUT_PWD/../LuaQt/release/LuaQt.lib
else:win32:CONFIG(debug, debug|release): LIBS += $$OUT_PWD/../LuaQt/debug/LuaQt.lib
else:unix: LIBS += -L$$OUT_PWD/../LuaQt/ -lLuaQt

