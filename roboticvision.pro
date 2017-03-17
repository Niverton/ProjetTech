#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T15:40:16
#
#-------------------------------------------------

QT       += core                                                \
            gui                                                 \
            multimedia                                          \
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoboticVision
TEMPLATE = app

CONFIG += c++11 debug

#INCLUDEPATH += include/
#LIBS +=                                                         \
#        -L/usr/lib                                              \
#        -lopencv_core                                           \
#        -lopencv_imgproc                                        \
#        -lopencv_features2d                                     \
#        -lopencv_flann                                          \
#        -lopencv_calib3d                                        \
#        -lopencv_nonfree                                        \
#        -ldl

# H. Decoudras configuration (please do not remove)
INCLUDEPATH                                                     \
            += include/                                         \
            += /usr/local/opencv-2.4.13/include

LIBS +=                                                         \
        -L/usr/local/opencv-2.4.13/lib                          \
        -lopencv_core                                           \
        -lopencv_imgproc                                        \
        -lopencv_highgui                                        \
        -lopencv_features2d                                     \
        -lopencv_flann                                          \
        -lopencv_calib3d                                        \
        -lopencv_nonfree                                        \
        -lopencv_gpu \
        -ldl

SOURCES +=                                                      \
    src/main.cpp                                                \
    src/mainwindow.cpp                                          \
    src/widgets/aboutwidget.cpp                                 \
    src/widgets/parametersdockwidget.cpp                        \
    src/widgets/images/imagewidget.cpp                          \
    src/widgets/images/stereotransformwidget.cpp                \
    src/parameters/blurparameters.cpp                           \
    src/processors/imageprocessor.cpp                           \
    src/utils/undostack.cpp                                     \
    src/parameters/parameters.cpp                               \
    src/parameters/sobelparameters.cpp                          \
    src/widgets/blurparameterswidget.cpp                        \
    src/parameters/parameterobservers.cpp                       \
    src/widgets/sobelparameterswidget.cpp                       \
    src/parameters/cannyparameters.cpp                          \
    src/widgets/cannyparameterswidget.cpp                       \
    src/utils/signalblocker.cpp                                 \
    src/except/parametersdockwidgetgeneratorexception.cpp       \
    src/utils/applicationstates.cpp                             \
    src/widgets/mainstatusbarwidget.cpp                         \
    src/except/applicationstatesnullstereowidget.cpp            \
    src/parameters/disparitymapparameters.cpp                   \
    src/widgets/disparitymapparameterswidget.cpp                \
    src/widgets/parameterswidget.cpp                            \
    src/widgets/cudagpuinfowidget.cpp                           \
    src/utils/cudartgpuinfodl.cpp                               \
    src/except/cudartresolveexception.cpp                       \
    src/except/cudartnotfoundexception.cpp                      \
    src/widgets/videos/videowidget.cpp \
    src/widgets/images/imagecropwidget.cpp \
    src/widgets/images/stereoimageswidget.cpp \
    src/except/filenotfoundexception.cpp \
    src/except/framereadfailureexception.cpp

HEADERS  +=                                                     \
    include/mainwindow.hpp                                      \
    include/widgets/aboutwidget.hpp                             \
    include/widgets/parametersdockwidget.hpp                    \
    include/widgets/images/imagewidget.hpp                      \
    include/widgets/images/stereotransformwidget.hpp            \
    include/parameters/blurparameters.hpp                       \
    include/processors/imageprocessor.hpp                       \
    include/utils/undostack.hpp                                 \
    include/parameters/parameters.hpp                           \
    include/parameters/sobelparameters.hpp                      \
    include/widgets/blurparameterswidget.hpp                    \
    include/parameters/parameterobservers.hpp                   \
    include/widgets/sobelparameterswidget.hpp                   \
    include/parameters/cannyparameters.hpp                      \
    include/widgets/cannyparameterswidget.hpp                   \
    include/utils/signalblocker.hpp                             \
    include/except/parametersdockwidgetgeneratorexception.hpp   \
    include/utils/applicationstates.hpp                         \
    include/widgets/mainstatusbarwidget.hpp                     \
    include/except/applicationstatesnullstereowidget.hpp        \
    include/parameters/disparitymapparameters.hpp               \
    include/widgets/disparitymapparameterswidget.hpp            \
    include/widgets/parameterswidget.hpp                        \
    include/widgets/cudagpuinfowidget.hpp                       \
    include/utils/cudartgpuinfodl.hpp                           \
    include/except/cudartresolveexception.hpp                   \
    include/except/cudartnotfoundexception.hpp                  \
    include/widgets/videos/videowidget.hpp \
    include/widgets/images/imagecropwidget.hpp \
    include/widgets/images/stereoimageswidget.hpp \
    include/except/filenotfoundexception.hpp \
    include/except/framereadfailureexception.hpp

RESOURCES +=                                                    \
    resources/styles/styles.qrc                                 \
    resources/logos/logos.qrc                                   \
    resources/images/images.qrc
