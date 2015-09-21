#-------------------------------------------------
#
# Project created by QtCreator 2015-09-04T09:48:29
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LCDPhont
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    symboldata.cpp \
    symboleditor.cpp \
    symbollist.cpp \
    symboldelegate.cpp

HEADERS  += mainwindow.h \
    symboldata.h \
    symboleditor.h \
    symbollist.h \
    symboldelegate.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
