#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagetools.hpp"
#include "undostack.hpp"

#include <QMainWindow>

#include <opencv2/core/core.hpp>

class ImageWidget;

class MainWindow : public QMainWindow {
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
     * \brief Displays the "About" modal window.
     */
    void renderAbout();

    /*!
     * \brief Allows the user to import an image.
     */
    void openFile();
    
    /*!
     * \brief Previous manipulation
     */
    void undoSlot();

    /*!
     * \brief Cuts an image.
     */
    void cutImgSlot();

    // Not implemented yet.
    void clipImgSlot();

    /*!
     * \brief Blurs an image.
     */
    void blurSlot();

    /*!
     * \brief Applies a sobel filter to an image.
     */
    void sobelSlot();

    /*!
     * \brief Applies a canny filter to an image.
     */
    void cannySlot();

    /*!
     * \brief Gets the disparity map of a pair of images.
     *        Disparity refers to the difference in location of an object in corresponding two
     *        (left and right) images as seen by the left and right eye which is created due to
     *        parallax (eyes’ horizontal separation). The brain uses this disparity to calculate
     *        depth information from the two dimensional images.
     */
    void dispMapSlot();

    //void depthMapSlot();  //  disparity map == depth map ?

    /*!
     * \brief flannSlot
     */
    void flannSlot();

  private:
    /*!
     * \brief Init all menus and actions in the menu bar
     */
    void initMenuBar();

    bool drawLeft;                      /*!< Indicates if the left image is drawn. */
    bool drawRight;                     /*!< Indicates if the right image is drawn. */

    ImageWidget* imageLeft;             /*!< Left image. */
    ImageWidget* imageRight;            /*!< Right image. */

    UndoStack undoStack;
};

#endif // MAINWINDOW
