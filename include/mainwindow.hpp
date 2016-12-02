#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagetools.hpp"
#include "imagewidget.hpp"

#include <QMainWindow>
#include <QLabel>

#include <opencv2/imgproc/imgproc.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();
    void adjustSize();

  private slots:
    void renderAbout();
    void openFile();
    void cutImgSlot();
    void clipImgSlot();
    void blurSlot();
    void sobelSlot();
    void cannySlot();
    void dispMapSlot();
    void flannSlot();

  private:
    //Foo
    /*!
     * \brief Init all menus and actions in the menu bar
     */
    void initMenuBar();

    //Vars
    bool drawLeft; //Are labels drawn
    bool drawRight;

    //Widget
    ImageWidget* imageLeft;
    ImageWidget* imageRight;
};

#endif // MAINWINDOW