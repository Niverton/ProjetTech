#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QImageReader>
#include <QLabel>
#include <QPixmap>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    void createMenus();
    void deleteMenus();

    void createActions();
    void deleteActions();

    QMenu* menu_about;
    QMenu* menu_file;

    QAction* action_about;
    QAction* action_open_file;
    QAction* action_quit;

    QLabel* image_label;
    void display_image(QString path);
    QPixmap pix_map;

  private slots:
    void about();
    void openFile();
    void quit();
};

#endif // MAINWINDOW_H
