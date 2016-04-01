TEMPLATE = app
CONFIG += console -std=c++14
CONFIG -= qt app_bundle

QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra -pedantic

INCLUDEPATH += ../../include

SOURCES += ./main.cpp
