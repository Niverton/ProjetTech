#include "mainwindow.h"
#include "stereowindow.h"
#include "cropwindow.h"

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
#include <QMouseEvent>
#include <QRubberBand>

/**********************************************************************
 **********************************************************************
 *
 * ctor
 *
 **********************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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
    setCentralWidget(central);

    //Ajuster le taille de la fenêtre en fonction de la taille de l'image.
    adjustSize();
    // Initting menu bar
    initMenuBar();

    imgLabel_= new QLabel(this);
    layout_->addWidget(imgLabel_);

    statusLabel_ = new QLabel(statusBar());
    statusBar()->addWidget(statusLabel_);

    // Connecting menu events
    connect(openAction_, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(quitAction_, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    connect(aboutAction_, SIGNAL(triggered(bool)), this, SLOT(renderMessageBox()));
    connect(cutAction_, SIGNAL(triggered(bool)), this, SLOT(cutImgSlot()));
    connect(clipAction_, SIGNAL(triggered(bool)), this, SLOT(clipImgSlot()));
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
  menuFile_ = new QMenu("&Fichier", mBar);
  //File - Open
  openAction_ = new QAction("&Ouvrir", menuFile_);
  openAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  menuFile_->addAction(openAction_);
  //File - Quit
  quitAction_ = new QAction("&Quitter", menuFile_);
  quitAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  menuFile_->addAction(quitAction_);

  //Edit
  menuEdit_ = new QMenu("&Editer", mBar);
  //Edit - cut
  cutAction_ = new QAction("&Couper l'image", menuEdit_);
  cutAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
  menuEdit_->addAction(cutAction_);
  //Edit - clipAction_
  clipAction_ = new QAction("&Rogner l'image", menuEdit_);
  clipAction_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  menuEdit_->addAction(clipAction_); //TODO

  //About
  menuAbout_ = new QMenu("À &Propos", mBar);
  aboutAction_ = new QAction("À &Propos", menuAbout_);
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
    QPixmap pxM = QPixmap::fromImage(imageLoaded_);
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
    QMessageBox::about(this, "A propos", "Projet technologique L3");
}

/**********************************************************************
 **********************************************************************
 *
 * Opens a file.
 *
 **********************************************************************/
void MainWindow::openFile()
{
    QString p = QFileDialog::getOpenFileName(this, "Ouvrir", QString(), "Images (*.png *.jpg)");

    if(!p.isEmpty())
    {
        path_ = p;
        statusLabel_->setText(p);
        // timer pour virer le texte.
        imageLoaded_ = QImage();
        imageLoaded_.load(p);
        imageLoadedIsDraw_ = true;

        // Sous Qt5.3.2 et 5.7 -> Permet de ne pas utiliser le resize event.
        // Ne marche apparement pas chez tous.
        // Hadrien Decoudras.
        //imgLabel_->setScaledContents(true);

        imgLabel_->setPixmap(QPixmap::fromImage(imageLoaded_));
        adjustSize();
    }
}

/*
*   Action cut
*/
void MainWindow::cutImgSlot(){
  if (!imageLoadedIsDraw_){
    return;
  }
    StereoWindow *w = new StereoWindow(&imageLoaded_);
    w->show();
}

/*
 *  Action clip
 */
void MainWindow::clipImgSlot(){
  if (!imageLoadedIsDraw_){
    return;
  }
    CropWindow *w = new CropWindow(&imageLoaded_);
    w->show();
}
