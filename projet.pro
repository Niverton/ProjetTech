#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T15:40:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet
TEMPLATE = app

CONFIG += c++11 debug

LIBS += -L/usr/lib -lopencv_core -lopencv_imgproc

SOURCES += src/projet.cpp \
    src/mainwindow.cpp

HEADERS  += include/mainwindow.hpp
