#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T00:08:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += widgets

TARGET = MainMenu_Test_01
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mainmenu.cpp \
<<<<<<< HEAD
    options.cpp

HEADERS += \
    mainmenu.h \
    options.h
=======
    newgame.cpp \
    start.cpp

HEADERS += \
    mainmenu.h \
    newgame.h \
    start.h
>>>>>>> fluxx/Main_Menu_Prototype

QMAKE_CXXFLAGS += -std=c++11
