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
#include <QStyle>
#include <QDesktopWidget>
#include <QResizeEvent>

/**********************************************************************
 **********************************************************************
 *
 * ctor
 *
 **********************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QRect r = QApplication::desktop()->screenGeometry();
    resize(r.width() * 0.5f, r.height() * 0.5f);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    //imgLabel_ = new QLabel(this);
    imgLabelLeft_ = new QLabel(this);
    imgLabelRight_ = new QLabel(this);
    //setCentralWidget(imgLabel_);
    setCentralWidget(imgLabelLeft_);
    initMenuBar();

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

void MainWindow::initMenuBar() {
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
}


/**********************************************************************
 **********************************************************************
 *
 * Resize.
 *
 **********************************************************************/
void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    if(!path_.isEmpty())
    {
        resizeLoadedImage();
    }
}

/**********************************************************************
 **********************************************************************
 *
 * Loaded image /*.
 *
 **********************************************************************/
void MainWindow::resizeLoadedImage()
{
    QPixmap pxM = QPixmap::fromImage(image_);
    QPixmap* pxmA = const_cast<QPixmap*>(imgLabel_->pixmap());
    QPixmap pxmB = pxM.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pxmA->swap(static_cast<QPixmap&>(pxmB));
}

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

    if(!p.isEmpty())
    {
        path_ = p;
        statusLabel_->setText(p);
        // timer pour virer le texte.

        image_.load(p);
        cutImage(&image_);

        // Sous Qt5.3.2 et 5.7 -> Permet de ne pas utiliser le resize event.
        // Ne marche apparement pas chez tous.
        // Hadrien Decoudras.
        //imgLabel_->setScaledContents(true);

        //imgLabel_->setPixmap(QPixmap::fromImage(image_));²
        imgLabelLeft_->setPixmap(QPixmap::fromImage(imageLeft_));           //coreDump
        //imgLabelRight_->setPixmap(QPixmap::fromImage(imageRight_));         //coreDump
        resizeLoadedImage();
    }
}

void MainWindow::cutImage(QImage* img){
  int imageWidth = img->width();
  int imageHeight = img->height();

  imageLeft_ = img->copy(0, 0, imageWidth/2, imageHeight/2);
  imageRight_ = img->copy(imageWidth/2, imageHeight/2, imageWidth, imageHeight);
}
