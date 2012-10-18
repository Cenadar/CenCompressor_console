#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T16:38:48
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cencompressor_console
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ccompressor.cpp \
    chuffmantree.cpp \
    cfilewriter.cpp \
    cfilereader.cpp

HEADERS += \
    ccompressor.h \
    chuffmantree.h \
    cfilewriter.h \
    cfilereader.h

OTHER_FILES += \
    README.md
