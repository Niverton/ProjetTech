#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private slots:
        void about();

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

};

#endif // MAINWINDOW_H
