#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T11:54:27
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_namesortiteratortest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../Debugger/


SOURCES += tst_namesortiteratortest.cpp \
    ../../Debugger/namesortiterator.cpp \
    ../../Debugger/compositevar.cpp \
    ../../Debugger/idstorage.cpp \
    ../../Debugger/iterator.cpp \
    ../../Debugger/varitem.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS +=
