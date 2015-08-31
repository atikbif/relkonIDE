CONFIG += console

INCLUDEPATH += "../../LCD/"
INCLUDEPATH += "../gtest-1.7.0/include/"
INCLUDEPATH += "../gtest-1.7.0/"

SOURCES += \
    main.cpp \
    ../gtest-1.7.0/src/gtest.cc \
    ../gtest-1.7.0/src/gtest-all.cc \
    ../gtest-1.7.0/src/gtest-death-test.cc \
    ../gtest-1.7.0/src/gtest-filepath.cc \
    ../gtest-1.7.0/src/gtest-port.cc \
    ../gtest-1.7.0/src/gtest-printers.cc \
    ../gtest-1.7.0/src/gtest-test-part.cc \
    ../gtest-1.7.0/src/gtest-typed-test.cc
