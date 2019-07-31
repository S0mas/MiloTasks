TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console
QMAKE_CXXFLAGS += /std:c++17

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
