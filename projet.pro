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

INCLUDEPATH += include/
LIBS += -L/usr/lib -lopencv_core -lopencv_imgproc -lopencv_features2d -lopencv_flann -lopencv_calib3d -lopencv_nonfree -lopencv_highgui

# H. Decoudras configuration (please do not remove)
#INCLUDEPATH += include/                             \
#               /usr/local/opencv-2.4.13/include
#LIBS += -L/usr/local/opencv-2.4.13/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_flann -lopencv_calib3d -lopencv_nonfree

SOURCES += src/projet.cpp \
    src/mainwindow.cpp \
    src/imagetools.cpp \
    src/imagewidget.cpp \
    src/undostack.cpp \
    src/libImageTools.cpp
HEADERS  += include/mainwindow.hpp \
    include/imagetools.hpp \
    include/imagewidget.hpp \
    include/undostack.hpp
