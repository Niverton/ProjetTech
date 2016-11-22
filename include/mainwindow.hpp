#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include <opencv2/imgproc/imgproc.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();

  private slots:
    void renderAbout();
    void openFile();
    void cutImgSlot();
    void clipImgSlot();
    void blurSlot();
    void sobelSlot();
    void cannySlot();

  private:
    //Foo
    /*!
     * \brief Init all menus and actions in the menu bar
     */
    void initMenuBar();
    /*!
     * \brief Updates QLabels from cv::Mats
     */
    void updateImages();

    //Vars
    bool drawLeft; //Are labels drawn
    bool drawRight;

    //Widget
    QLabel* imageLeft;
    QLabel* imageRight;


    //OpenCV
    cv::Mat matLeft;
    cv::Mat matRight;
    
};

#endif // MAINWINDOW