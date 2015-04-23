#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T10:37:16
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rIDE
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    foldingwidget.cpp \
    highlightalgorithm.cpp \
    highlightalgorithmfactory.cpp \
    highlightbrackets.cpp \
    highlighter.cpp \
    highlightkeyword.cpp \
    highlightmultilinecomments.cpp \
    highlightsettingsreader.cpp \
    inpdatainterface.cpp \
    leftverticalwidget.cpp \
    linenumberswidget.cpp \
    konTranslator/abstractchfilesfactory.cpp \
    konTranslator/chgenerator.cpp \
    konTranslator/freertosfactory.cpp \
    konTranslator/freertosgenerator.cpp \
    konTranslator/konparser.cpp \
    konTranslator/konprocess.cpp \
    konTranslator/moduleio.cpp \
    konTranslator/situation.cpp \
    konTranslator/textblock.cpp \
    RCompiler/rcompiler.cpp \
    prbuilder.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    foldingwidget.h \
    highlightalgorithm.h \
    highlightalgorithmfactory.h \
    highlightbrackets.h \
    highlighter.h \
    highlightkeyword.h \
    highlightmultilinecomments.h \
    highlightsettingsreader.h \
    inpdatainterface.h \
    leftverticalwidget.h \
    linenumberswidget.h \
    konTranslator/abstractchfilesfactory.h \
    konTranslator/chgenerator.h \
    konTranslator/freertosfactory.h \
    konTranslator/freertosgenerator.h \
    konTranslator/konparser.h \
    konTranslator/konprocess.h \
    konTranslator/moduleio.h \
    konTranslator/situation.h \
    konTranslator/textblock.h \
    RCompiler/rcompiler.h \
    prbuilder.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
