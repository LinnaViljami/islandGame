#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T11:30:54
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = gamestatetest
CONFIG += c++14
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    gamestatetest.cc \
    ../../../UI/gamestate.cc

HEADERS += \
    ../../../UI/gamestate.hh


DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += \
            ../../../UI/ \
            ../../../GameLogic/Engine/