#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T15:51:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RRT
TEMPLATE = app


SOURCES += main.cpp\
        rrt.cpp \
    mylabel.cpp \
    node.cpp

HEADERS  += rrt.h \
    mylabel.h \
    node.h

FORMS    += rrt.ui

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/lib/x86_64-linux-gnu/libopencv_highgui.so  \
        /usr/lib/x86_64-linux-gnu/libopencv_core.so \
        /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so
