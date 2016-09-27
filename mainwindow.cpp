#include "mainwindow.h"

#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QFileDialog>
#include <QStatusBar>
#include <QLabel>
#include <QApplication>
#include <QImageReader>

/**********************************************************************
 **********************************************************************
 *
 * ctor
 *
 **********************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    imgLabel_ = new QLabel(this);
    setCentralWidget(imgLabel_);

    QMenuBar* mBar = menuBar();
    menuFile_ = new QMenu("File", mBar);
    openAction_ = new QAction("Open", menuFile_);
    openAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menuFile_->addAction(openAction_);

    quitAction_ = new QAction("Quit", menuFile_);
    quitAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    menuFile_->addAction(quitAction_);

    menuAbout_ = new QMenu("About", mBar);
    aboutAction_ = new QAction("About", menuAbout_);
    aboutAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    menuAbout_->addAction(aboutAction_);


    mBar->addMenu(menuFile_);
    mBar->addMenu(menuAbout_);

    statusLabel_ = new QLabel(statusBar());
    statusBar()->addWidget(statusLabel_);

    connect(openAction_, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(quitAction_, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    connect(aboutAction_, SIGNAL(triggered(bool)), this, SLOT(renderMessageBox()));
}

/**********************************************************************
 **********************************************************************
 *
 * Default dtor. Pas besoin de destroy si parent<->enfant.
 *
 **********************************************************************/
MainWindow::~MainWindow() {}

/**********************************************************************
 **********************************************************************
 *
 * Renders message box.
 *
 **********************************************************************/
void MainWindow::renderMessageBox()
{
    QMessageBox::about(this, "About", "About QMessageBox");
}

/**********************************************************************
 **********************************************************************
 *
 * Opens a file.
 *
 **********************************************************************/
void MainWindow::openFile()
{
    QString p = QFileDialog::getOpenFileName(this, "Open", QString(), "Images (*.png *.jpg)");
    path_ = p.toUtf8().constData();
    statusLabel_->setText(p);
    // timer pour virer le texte.

    QPixmap pxM(p);
    imgLabel_->setPixmap(pxM);
}
