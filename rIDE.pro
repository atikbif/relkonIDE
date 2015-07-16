#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T10:37:16
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += serialport

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
    prbuilder.cpp \
    settingsform.cpp \
    settingsbase.cpp \
    Protocols/request.cpp \
    Protocols/rk.cpp \
    Protocols/commandinterface.cpp \
    Protocols/commanddecorator.cpp \
    Protocols/rkcommand.cpp \
    Protocols/asciidecorator.cpp \
    Protocols/udpdecorator.cpp \
    AutoSearch/scanuart.cpp \
    AutoSearch/scancontroller.cpp \
    AutoSearch/scangui.cpp \
    Protocols/checksum.cpp \
    AutoSearch/detectedcontroller.cpp \
    Loader/bootmodesetter.cpp \
    Loader/ymodem.cpp \
    Loader/ymodemthread.cpp \
    Loader/sysframreadwrite.cpp \
    Loader/sfram.cpp \
    Debugger/varitem.cpp \
    Debugger/compositevar.cpp \
    Debugger/iterator.cpp \
    Debugger/namesortiterator.cpp \
    Debugger/debuggerform.cpp \
    Debugger/idgenerator.cpp \
    Debugger/idstorage.cpp \
    Debugger/varscreator.cpp \
    Debugger/memblock.cpp \
    Debugger/memstorage.cpp \
    Debugger/Scanner/scanmanager.cpp \
    Debugger/Scanner/plcscanner.cpp

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
    prbuilder.h \
    settingsform.h \
    settingsbase.h \
    Protocols/request.h \
    Protocols/rk.h \
    Protocols/commandinterface.h \
    Protocols/commanddecorator.h \
    Protocols/rkcommand.h \
    Protocols/asciidecorator.h \
    Protocols/udpdecorator.h \
    AutoSearch/scanuart.h \
    AutoSearch/scancontroller.h \
    AutoSearch/scangui.h \
    Protocols/checksum.h \
    AutoSearch/detectedcontroller.h \
    Loader/bootmodesetter.h \
    Loader/ymodem.h \
    Loader/ymodemthread.h \
    Loader/sysframreadwrite.h \
    Loader/sfram.h \
    Debugger/varitem.h \
    Debugger/compositevar.h \
    Debugger/iterator.h \
    Debugger/namesortiterator.h \
    Debugger/debuggerform.h \
    Debugger/idgenerator.h \
    Debugger/idstorage.h \
    Debugger/varscreator.h \
    Debugger/memblock.h \
    Debugger/memstorage.h \
    Debugger/Scanner/scanmanager.h \
    Debugger/Scanner/plcscanner.h

FORMS    += mainwindow.ui \
    settingsform.ui \
    AutoSearch/scangui.ui \
    Loader/ymodemthread.ui \
    Loader/sysframreadwrite.ui \
    Debugger/debuggerform.ui

RESOURCES += \
    icons.qrc


INCLUDEPATH += "C:/boost/boost_1_58_0"

