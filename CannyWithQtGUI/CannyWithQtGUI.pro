#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T12:13:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CannyWithQtGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include(PRI\\OpenCV.pri)

INCLUDEPATH += $$PWD

