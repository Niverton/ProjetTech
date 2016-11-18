#ifndef MAINWINDOW_H
#define MAINWINDOW

#include <QMainWindow>
#include <QLabel>

#include <opencv2/imgproc/imgproc.hpp>

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();

  private:
    //Widget
    QLabel* imageLeft;
    QLabel* imageRight;


    //OpenCV
    cv::Mat imageLeft;
    cv::Mat imageRight;
    
};

#endif // MAINWINDOW