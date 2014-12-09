#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T00:08:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += widgets

QT      += testlib

TARGET = Fluxx
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$PWD

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
    switchplayer.cpp \
    ../../src/BoardSnapshot.cc \
    ../../src/Card.cc \
    ../../src/CardContainer.cc \
    ../../src/CardContainerManager.cc \
    ../../src/CardManager.cc \
    ../../src/Deck.cc \
    ../../src/DeckParser.cc \
    ../../src/GameLogic.cc \
    ../../src/GameLoop.cc \
    ../../src/Player.cc \
    ../../src/PlayerManager.cc \
    ../../src/RuleManager.cc \
    ../../src/SessionData.cc \
    ../../src/Stock.cc \
    ../../src/PlayerID.cc \
    ../../src/TriggeredRule.cc \
    bigcardcollection.cpp \
    cardcollection.cpp \
    cardidloop.cpp \
    playerloop.cpp \
    cardpicture.cpp


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
    cardbutton.h \
    playerlistitem.h \
    trashbutton.h \
    deckbutton.h \
    goalbuttons.h \
    bigcard.h \
    activehand.h \
    profile.h \
    activekeepers.h \
    switchplayer.h \
    bigcardcollection.h \
    cardcollection.h \
    profilename.h \
    cardidloop.h \
    ../../include/BoardSnapshot.h \
    ../../include/Card.h \
    ../../include/CardContainer.h \
    ../../include/CardContainerID.h \
    ../../include/CardContainerManager.h \
    ../../include/CardID.h \
    ../../include/CardManager.h \
    ../../include/Deck.h \
    ../../include/DeckParser.h \
    ../../include/Effect.h \
    ../../include/enums.h \
    ../../include/GameLogic.h \
    ../../include/GameLoop.h \
    ../../include/Player.h \
    ../../include/PlayerID.h \
    ../../include/PlayerManager.h \
    ../../include/RuleManager.h \
    ../../include/SessionData.h \
    ../../include/Stock.h \
    ../../include/TriggeredRule.h \
    playerloop.h \
    cardpicture.h \
    ../../include/PlayerStats.h


QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES +=

RESOURCES += \
    images.qrc \
    textfiles.qrc
