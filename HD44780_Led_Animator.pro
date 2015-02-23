#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T10:53:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HD44780_Led_Animator
TEMPLATE = app


SOURCES += main.cpp\
        animationwindow.cpp \
    ledmatrix.cpp \
    simframe.cpp \
    frame.cpp

HEADERS  += animationwindow.h \
    ledmatrix.h \
    simframe.h \
    frame.h

FORMS    += animationwindow.ui
