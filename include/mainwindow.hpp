#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagetools.hpp"
#include "imagewidget.hpp"

#include <stack>
#include <QMainWindow>

#include <opencv2/core/core.hpp>

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

    // Non implemented yet.
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
    /*!
     * \brief Change widget images and add previous to the stacks
     */
    void changeImages(cv::Mat& left, cv::Mat& right);

    //Vars
    bool drawLeft; //Are labels drawn
    bool drawRight;
    std::stack<cv::Mat> undoStackLeft; //Stack of previous images
    std::stack<cv::Mat> undoStackRight;

    //Widget
    ImageWidget* imageLeft;
    ImageWidget* imageRight;
};

#endif // MAINWINDOW
