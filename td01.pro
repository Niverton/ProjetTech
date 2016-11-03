#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T15:40:16
#
#-------------------------------------------------

CONFIG += debug_and_release

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetTech
TEMPLATE = app

CONFIG += c++11

LIBS += -L/usr/lib -lopencv_core -lopencv_imgproc

SOURCES += main.cpp\
        mainwindow.cpp\
        stereowindow.cpp\
        cropwindow.cpp\
        processingwindow.cpp \
    imagetools.cpp \
    imageprocessor.cpp

HEADERS  += mainwindow.h\
        stereowindow.h\
        cropwindow.h\
        processingwindow.h \
    imagetools.h \
    imageprocessor.h
