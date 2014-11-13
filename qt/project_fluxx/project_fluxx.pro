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
    ../../src/BoardSnapshot.cc \
    ../../src/Card.cc \
    ../../src/CardContainer.cc \
    ../../src/CardContainerManager.cc \
    ../../src/CardID.cc \
    ../../src/CardManager.cc \
    ../../src/ContainerID.cc \
    ../../src/Deck.cc \
    ../../src/Effect.cc \
    ../../src/GameLogic.cc \
    ../../src/GameLoop.cc \
    ../../src/GUISystem.cc \
    ../../src/Player.cc \
    ../../src/PlayerID.cc \
    ../../src/PlayerManager.cc \
    ../../src/RuleManager.cc \
    ../../src/SessionData.cc \
    ../../src/Stock.cc \
    ../../src/TriggeredRule.cc

HEADERS += \
    mainmenu.h \
    newgame.h \
    start.h \
    options.h \
    ../../include/BoardSnapshot.h \
    ../../include/Card.h \
    ../../include/CardContainer.h \
    ../../include/CardContainerManager.h \
    ../../include/CardID.h \
    ../../include/CardManager.h \
    ../../include/ContainerID.h \
    ../../include/Deck.h \
    ../../include/Effect.h \
    ../../include/GameLogic.h \
    ../../include/GameLoop.h \
    ../../include/GUISystem.h \
    ../../include/MainMenu.h \
    ../../include/Player.h \
    ../../include/PlayerID.h \
    ../../include/PlayerManager.h \
    ../../include/RuleManager.h \
    ../../include/SessionData.h \
    ../../include/Stock.h \
    ../../include/TriggeredRule.h

QMAKE_CXXFLAGS += -std=c++11
