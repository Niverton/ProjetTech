#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private slots:


    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        QMenu toolbar;
};

#endif // MAINWINDOW_H
