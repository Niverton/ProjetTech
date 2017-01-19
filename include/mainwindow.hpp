#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagetools.hpp"
#include "imagewidget.hpp"

#include <stack>
#include <QMainWindow>
#include <QLabel>

#include <opencv2/core/core.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();
    void adjustSize();

  private slots:
    void renderAbout();
    void openFile();
    void undoSlot();
    void cutImgSlot();
    void clipImgSlot();
    void blurSlot();
    void sobelSlot();
    void cannySlot();
    void dispMapSlot();
    //void depthMapSlot();  //  disparity map == depth map ? 
    void flannSlot();

  private:
    //Foo
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