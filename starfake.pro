TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    texturemanager.cpp

HEADERS += \
    texturemanager.h \
    starship.h \
    bullet.h \
    coordpoint.h

LIBS += -lGL -lGLU -lglut -lfreeimage

DISTFILES += \
    Makefile
