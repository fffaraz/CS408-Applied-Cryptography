TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    hillcipher.cpp \
    hillcipher3.cpp

HEADERS += \
    hillcipher.h \
    hillcipher3.h

