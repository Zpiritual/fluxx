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

INCLUDEPATH += $$PWD/../../include

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
    playerlistitem.cpp \
    trashbutton.cpp \
    deckbutton.cpp \
    goalbuttons.cpp \
    bigcard.cpp \
    activehand.cpp \
    profile.cpp \
    activekeepers.cpp \
    switchplayer.cpp

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
    playerlistitem.h \
    trashbutton.h \
    deckbutton.h \
    goalbuttons.h \
    bigcard.h \
    activehand.h \
    profile.h \
    activekeepers.h \
    switchplayer.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES +=

RESOURCES += \
    images.qrc \
    textfiles.qrc
