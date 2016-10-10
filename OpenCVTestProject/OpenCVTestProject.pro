#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T11:21:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVTestProject
TEMPLATE = app

INCLUDEPATH += "D:\\OpenCV\\build\\include" \

CONFIG(debug,debug|release)
{
    LIBS += -L"D:\\OpenCV\\build\\x64\\vc14\\lib" \
            -lopencv_world310d
}

CONFIG(release,debug|release)
{
    LIBS += -L"D:\\OpenCV\\build\\x64\\vc14\\lib" \
            -lopencv_world310
}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
