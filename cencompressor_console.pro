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
    cbitreader.cpp \
    logger.cpp \
    cbitwriter.cpp

HEADERS += \
    ccompressor.h \
    chuffmantree.h \
    logger.h \
    cbitreader.h \
    cbitwriter.h

OTHER_FILES += \
    README.md
