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
    newgame.cpp \
    start.cpp \
    options.cpp \
    gui.cpp \
    logwidget.cpp \
    playerlist.cpp \
    rulesgridwidget.cpp \
    activeplayer.cpp \
    cardbutton.cpp \
    playerlistitem.cpp

HEADERS += \
    mainmenu.h \
    newgame.h \
    start.h \
    options.h \
    gui.h \
    logwidget.h \
    playerlist.h \
    rulesgridwidget.h \
    activeplayer.h \
    ../../include/BoardSnapshot.h \
    ../../include/CardID.h \
    cardbutton.h \
    playerlistitem.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES +=

RESOURCES += \
    images.qrc
