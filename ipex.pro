TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
CONFIG += link_pkgconfig

SOURCES += main.cpp \
    smbus.cpp
HEADERS += \
    SLABCP2112.h \
    Types.h \
    smbus.h


INCLUDEPATH += "$$_PRO_FILE_PWD_"
DEPENDPATH += "$$_PRO_FILE_PWD_"
QMAKE_LIBDIR += "$$_PRO_FILE_PWD_"
LIBS += "$$_PRO_FILE_PWD_/libslabhidtosmbus.so.1"
LIBS += "$$_PRO_FILE_PWD_/libslabhiddevice.so.1"
