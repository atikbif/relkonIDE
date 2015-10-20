#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T11:13:13
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = main.ico
VERSION = 1.0.0.1
QMAKE_TARGET_COMPANY = Kontel Co
QMAKE_TARGET_PRODUCT = RKLink Utility Application
QMAKE_TARGET_DESCRIPTION = RKLink Utility
QMAKE_TARGET_COPYRIGHT = Kontel

CONFIG += c++11

TARGET = Reloader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AutoSearch/detectedcontroller.cpp \
    AutoSearch/scancontroller.cpp \
    AutoSearch/scangui.cpp \
    AutoSearch/scanuart.cpp \
    Loader/bootmodesetter.cpp \
    Loader/sfram.cpp \
    Loader/sysframreadwrite.cpp \
    Loader/ymodem.cpp \
    Loader/ymodemthread.cpp \
    Protocols/asciidecorator.cpp \
    Protocols/checksum.cpp \
    Protocols/commanddecorator.cpp \
    Protocols/commandinterface.cpp \
    Protocols/request.cpp \
    Protocols/rk.cpp \
    Protocols/rkcommand.cpp \
    Protocols/udpdecorator.cpp \
    memstorage.cpp \
    Loader/flashread.cpp \
    Loader/flash.cpp

HEADERS  += mainwindow.h \
    AutoSearch/detectedcontroller.h \
    AutoSearch/scancontroller.h \
    AutoSearch/scangui.h \
    AutoSearch/scanuart.h \
    Loader/bootmodesetter.h \
    Loader/sfram.h \
    Loader/sysframreadwrite.h \
    Loader/ymodem.h \
    Loader/ymodemthread.h \
    Protocols/asciidecorator.h \
    Protocols/checksum.h \
    Protocols/commanddecorator.h \
    Protocols/commandinterface.h \
    Protocols/request.h \
    Protocols/rk.h \
    Protocols/rkcommand.h \
    Protocols/udpdecorator.h \
    memstorage.h \
    Loader/flashread.h \
    Loader/flash.h

FORMS    += mainwindow.ui \
    AutoSearch/scangui.ui \
    Loader/sysframreadwrite.ui \
    Loader/ymodemthread.ui \
    Loader/flashread.ui

RESOURCES += \
    icons.qrc
