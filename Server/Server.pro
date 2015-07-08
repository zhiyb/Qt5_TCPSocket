#-------------------------------------------------
#
# Project created by QtCreator 2014-09-02T10:46:03
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    network.cpp \
    inputhandle.cpp \
    handle.cpp

HEADERS += \
    network.h \
    inputhandle.h \
    handle.h
