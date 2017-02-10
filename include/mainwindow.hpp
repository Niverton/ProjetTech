/*!
 * \file mainwindow.hpp
 * \brief Header containing the declaration of the MainWindow class which acts as the main entry point of the application.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "undostack.hpp"

#include <QMainWindow>

#include <opencv2/core/core.hpp>

class StereoImageWidget;
class StereoTransformWidget;
class AboutWidget;

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
     * \brief Wrapper used to adjust the size of the window.
     */
    void adjustSize();

private slots:
    /*!
     * \brief Displays the 'About' modal window.
     */
    void about();

    /*!
     * \brief Allows the user to import an image.
     */
    void open();
    
    /*!
     * \brief Previous manipulation.
     */
    void undo();

    /*!
     * \brief Cuts an image.
     */
    void cut();

    // Not implemented yet.
    void clip();

    /*!
     * \brief Blurs an image.
     */
    void blur();

    /*!
     * \brief Applies a sobel filter to an image.
     */
    void sobel();

    /*!
     * \brief Applies a canny filter to an image.
     */
    void canny();

    /*!
     * \brief Gets the disparity map of a pair of images.
     *        Disparity refers to the difference in location of an object in corresponding two
     *        (left and right) images as seen by the left and right eye which is created due to
     *        parallax (eyes’ horizontal separation). The brain uses this disparity to calculate
     *        depth information from the two dimensional images.
     */
    void disparity();

    //void depthMapSlot();  //  disparity map == depth map ?

    /*!
     * \brief flannSlot
     */
    void flann();

private:
    /*!
     * \brief Initializes all menus and actions of the menu bar
     */
    void initMenuBar();

    bool drawLeft;                              /*!< Indicates if the left image is drawn. */
    bool drawRight;                             /*!< Indicates if the right image is drawn. */

    StereoImageWidget* imageLeft;               /*!< Left image. */
    StereoImageWidget* imageRight;              /*!< Right image. */

    StereoTransformWidget* transformWidget;     /*!< OpenCV image transformation widget. */

    AboutWidget* aboutWidget;                   /*!< About modal window. */

    UndoStack undoStack;                        /*! Saved state of images. */
};

#endif // MAINWINDOW
