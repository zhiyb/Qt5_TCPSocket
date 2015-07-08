#-------------------------------------------------
#
# Project created by QtCreator 2014-09-02T10:45:41
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    network.cpp \
    inputhandle.cpp

HEADERS += \
    network.h \
    inputhandle.h
