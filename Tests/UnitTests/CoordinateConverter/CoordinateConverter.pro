#-------------------------------------------------
#
# Project created by QtCreator 2018-10-30T13:25:00
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = coordinateconvertertests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++14

TEMPLATE = app

DESTDIR = bin

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += --coverage
QMAKE_LFLAGS += --coverage

HEADERS += \
        ../../../UI/coordinateconverter.hh

SOURCES += \
        ../../../UI/coordinateconverter.cc \
    coordinateconvertertests.cc

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += \
            ../../../UI/ \
            ../../../GameLogic/Engine/

DEPENDPATH += \
            ../../../UI/ \
            ../../../GameLogic/Engine/
