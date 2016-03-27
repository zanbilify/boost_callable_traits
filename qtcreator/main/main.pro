TEMPLATE = app
CONFIG += console -std=c++14
CONFIG -= qt app_bundle

QMAKE_CXXFLAGS += -std=c++14 -stdlib=libc++ -Wall -Wextra -pedantic

LIBS += -lc++ -lc++abi

INCLUDEPATH += ../../include

SOURCES += ./main.cpp
