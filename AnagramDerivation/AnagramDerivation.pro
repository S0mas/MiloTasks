TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console
QT += quick
win32-msvc* {
QMAKE_CXXFLAGS += /std:c++latest
}
QMAKE_CXXFLAGS += -std=gnu++17

SOURCES += \
        anagramderivationsolver.cpp \
        anagramderivativenode.cpp \
        anagramsbase.cpp \
        main.cpp

HEADERS += \
    anagramderivationsolver.h \
    anagramderivativenode.h \
    anagramsbase.h \
    anagramstringhash.h \
    dictionaryparser.h \
    logger.h
