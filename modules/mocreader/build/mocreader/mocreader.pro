#-------------------------------------------------
#
# Project created by QtCreator 2014-08-30T21:39:50
#
#-------------------------------------------------

QT       -= gui

TARGET = mocreader
TEMPLATE = lib

DEFINES += MOCREADER_LIB

SOURCES += \
    ../../src/keywords.cpp      \
    ../../src/moc.cpp           \
    ../../src/mocparser.cpp     \
    ../../src/mocreader.cpp     \
    ../../src/parser.cpp        \
    ../../src/ppkeywords.cpp    \
    ../../src/preprocessor.cpp  \
    ../../src/token.cpp

HEADERS += \
    ../../src/moc.h             \
    ../../src/mocparser.h       \
    ../../src/mocreader.h       \
    ../../src/mocreader_global.h\
    ../../src/parser.h          \
    ../../src/preprocessor.h    \
    ../../src/qmetaobject_moc_p.h   \
    ../../src/symbols.h         \
    ../../src/token.h           \
    ../../src/utils.h

LIBS += -llua51

unix {
    target.path = /usr/lib
    INSTALLS += target
}
