#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setMenuBar(new QMenuBar());
    QMenu *m = new QMenu("About");
    QObject::connect(this->menuBar(), QMenuBar::triggered(m->action), this, &MainWindow::about);
    this->menuBar()->addMenu(m);

}

MainWindow::~MainWindow()
{

}

void MainWindow::about() {
    QMessageBox m = new QMessageBox("About", "Blah blah", NULL, NULL, NULL, NULL);
    m.show();
}
