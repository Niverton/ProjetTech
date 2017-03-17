/*!
 * \file mainwindow.hpp
 * \brief Header containing the declaration of the MainWindow class which acts as the main entry point of the application.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.4
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "utils/undostack.hpp"
#include "utils/applicationstates.hpp"

#include <QMainWindow>

#include <opencv2/core/core.hpp>

class StereoImagesWidget;
class ParametersDockWidget;
class ParameterObservers;
class StereoTransformWidget;
class CudaGPUInfoWidget;
class AboutWidget;
class MainStatusBarLeftWidget;
class MainStatusBarRightWidget;

class VideoWidget;

/*!
 * \class MainWindow
 * \brief The MainWindow class gathers all the functionalities of the program.
 *        It consists of two ImageWidget objects used to display a stereo picture.
 *        Several image transformations are availables such as: blur, canny or flann.
 *        The main purposes of this class is to represent a depth map and a disparity
 *        map from a stereo image.
 *        In addition to this, the MainWindow class features undo and zoom operations.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Default constructor.
     */
    MainWindow();

    /*!
     * \brief Default destructor.
     */
    ~MainWindow();

    /*!
     * \brief Initializes all menus and actions of the menu bar
     */
    void initMenuBar();

signals:
    void method(int which);

private slots:
    /*!
     * \brief Allows the user to import an image.
     */
    void open();

    /*!
     * \brief Previous manipulation.
     */
    void undo();

    void saveStereoTransitoryStates(bool value);

    /*!
     * \brief Cuts an image.
     */
    void cut();

    // Not implemented yet.
    void clip();

    void blurMenuClicked();
    void sobelMenuClicked();
    void cannyMenuClicked();
    void disparityMenuClicked();

    /*!
     * \brief Blurs an image.
     */
    void blur();
    void blurRealTime();

    /*!
     * \brief Applies a sobel filter to an image.
     */
    void sobel();
    void sobelRealTime();

    /*!
     * \brief Applies a canny filter to an image.
     */
    void canny();
    void cannyRealTime();

    /*!
     * \brief Gets the disparity map of a pair of images.
     *        Disparity refers to the difference in location of an object in corresponding two
     *        (left and right) images as seen by the left and right eye which is created due to
     *        parallax (eyes’ horizontal separation). The brain uses this disparity to calculate
     *        depth information from the two dimensional images.
     */
    void disparity();
    void disparityRealTime();

    //void depth();

    /*!
     * \brief flannSlot
     */
    void flann();

    void parametersDockWidgetClosed();

    void gpuInfo();

    /*!
     * \brief Displays the 'About' modal window.
     */
    void about();

private:
    void generateParametersDockWidget();

private:
    bool cudaRunTimeLibraryDetected;                                                /*!< Indicates if Cuda Run Time Library is present. */

private:
    StereoImagesWidget* stereoWidget;                                               /*!< Stereo image widget */
    VideoWidget*        videoWidget;

    ParametersDockWidget* parametersDockWidget;                                     /*!< Allows to manipulate OpenCV related attributes. */

    StereoTransformWidget* transformWidget;                                         /*!< OpenCV image transformation widget. */

    CudaGPUInfoWidget* gpuInfoWidget;                                               /*!< GPU modal window. */
    AboutWidget* aboutWidget;                                                       /*!< About modal window. */

    MainStatusBarLeftWidget* leftStatusBarWidget;                                   /*!< Left part of the status bar. */
    MainStatusBarRightWidget* rightStatusBarWidget;                                 /*!< Right part of the status bar. */

    ParameterObservers* observers;                                                  /*!< Observers of OpenCV related attributes. */

    ApplicationStates appStates;                                                    /*! Saved state of images. */
};

#endif // MAINWINDOW
