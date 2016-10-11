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
    //
    QRect r = QApplication::desktop()->screenGeometry();
    resize(r.width() * 0.5f, r.height() * 0.5f);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    /*  QMainWindow possède son propre layout qui lui permet de disposer les barres d'outils
        On est donc obligé de créer un widget qui contiendra le layout du contenu de la fenêtre
        getCentralWidget() pour récupèrer ce widget
    */
    QWidget *central = new QWidget(this);
    layout_ = new QHBoxLayout(this);
    central->setLayout(layout_);
    this->setCentralWidget(central);

    // Initting menu bar
    initMenuBar();

    statusLabel_ = new QLabel(statusBar());
    statusBar()->addWidget(statusLabel_);

    // Connecting menu events
    connect(openAction_, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(quitAction_, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    connect(aboutAction_, SIGNAL(triggered(bool)), this, SLOT(renderMessageBox()));
    connect(cutAction_, SIGNAL(triggered(bool)), this, SLOT(cutImgSlot()));
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
 * Init ufnction for menubar
 *
 **********************************************************************/
void MainWindow::initMenuBar() {
  QMenuBar* mBar = menuBar();

  //File
  menuFile_ = new QMenu("Fichier", mBar);
  //File - Open
  openAction_ = new QAction("Ouvrir", menuFile_);
  openAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  menuFile_->addAction(openAction_);
  //File - Quit
  quitAction_ = new QAction("Quitter", menuFile_);
  quitAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  menuFile_->addAction(quitAction_);

  //Edit
  menuEdit_ = new QMenu("Editer", mBar);
  //Edit - cut
  cutAction_ = new QAction("Couper l'image", menuEdit_);
  menuEdit_->addAction(cutAction_);

  //About
  menuAbout_ = new QMenu("À Propos", mBar);
  aboutAction_ = new QAction("À Propos", menuAbout_);
  aboutAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
  menuAbout_->addAction(aboutAction_);

  mBar->addMenu(menuFile_);
  mBar->addMenu(menuEdit_);
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
 * Loaded image.
 *
 **********************************************************************/
void MainWindow::resizeLoadedImage()
{
    /* TODO
    QPixmap pxM = QPixmap::fromImage(image_);
    QPixmap* pxmA = const_cast<QPixmap*>(imgLabel_->pixmap());
    QPixmap pxmB = pxM.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pxmA->swap(static_cast<QPixmap&>(pxmB));
    //*/

    // Work for image1
    //TODO
    // Work for image2
    // TODO
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
        imageLoaded_ = new QImage();
        imageLoaded_->load(p);

        // Sous Qt5.3.2 et 5.7 -> Permet de ne pas utiliser le resize event.
        // Ne marche apparement pas chez tous.
        // Hadrien Decoudras.
        //imgLabel_->setScaledContents(true);

        //imgLabel_->setPixmap(QPixmap::fromImage(image_));
        //imgLabelLeft_->setPixmap(QPixmap::fromImage(imageLeft_));
        //imgLabelRight_->setPixmap(QPixmap::fromImage(imageRight_));
        //resizeLoadedImage();
        drawImage(*imageLoaded_);   //On afficher l'image.

        //cutImage(imageLoaded_);
        //drawImages(imageLeft_, imageRight_);
    }
}

/**********************************************************************
 **********************************************************************
 *
 * Function splitting loaded image in two
 *
 **********************************************************************/
void MainWindow::cutImage(QImage* img){
  int imageWidth = img->width();
  int imageHeight = img->height();

  imageLeft_ = img->copy(0, 0, imageWidth/2, imageHeight);
  imageRight_ = img->copy(imageWidth/2, 0, imageWidth/2, imageHeight);
}

/*
*   Fonction permettant d'afficher une image
*/
void MainWindow::drawImage(QImage img){
  if (imagesCuttedIsDraw_){
    imgLabelLeft_->clear();
    imgLabelRight_->clear();
    layout_->removeWidget(imgLabelLeft_);
    layout_->removeWidget(imgLabelRight_);
    layout_->update();
  }

  imgLabel_ = new QLabel(this);
  layout_->addWidget(imgLabel_);
  imgLabel_->setPixmap(QPixmap::fromImage(img));
  imageLoadedIsDraw_ = true;
}

/*
*   Fonction permettant d'afficher deux images côte à côte
*/
void MainWindow::drawImages(QImage imgLeft, QImage imgRight){
  if (imageLoadedIsDraw_){
      imgLabel_->clear();
      layout_->removeWidget(imgLabel_);
      layout_->update();
  }

  imgLabelLeft_ = new QLabel(this);
  imgLabelRight_ = new QLabel(this);

  layout_->addWidget(imgLabelLeft_);
  layout_->addWidget(imgLabelRight_);

  imgLabelLeft_->setPixmap(QPixmap::fromImage(imgLeft));
  imgLabelRight_->setPixmap(QPixmap::fromImage(imgRight));
  imagesCuttedIsDraw_ = true;
}

/*
*   Action cut
*/
void MainWindow::cutImgSlot(){
  cutImage(imageLoaded_);
  drawImages(imageLeft_, imageRight_);
}
