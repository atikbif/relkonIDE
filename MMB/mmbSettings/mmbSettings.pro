#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T12:05:37
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = mmb.ico
VERSION = 1.0.0.1
QMAKE_TARGET_COMPANY = Kontel Co
QMAKE_TARGET_PRODUCT = MMBConfig
QMAKE_TARGET_DESCRIPTION = matchbox config utility
QMAKE_TARGET_COPYRIGHT = Kontel

TARGET = mmbSettings
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
