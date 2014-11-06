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
    mainmenu.cpp

HEADERS += \
    mainmenu.h \
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
