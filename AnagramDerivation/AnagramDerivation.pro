TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console
QMAKE_CXXFLAGS += /std:c++17

SOURCES += \
        main.cpp

HEADERS += \
    anagramderivative.h \
    anagramstringhash.h \
    dictionaryparser.h \
    findanagram.h \
    wordsbasemap.h
