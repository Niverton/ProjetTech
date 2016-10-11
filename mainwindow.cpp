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

    //
    imgLabelLeft_ = new QLabel(this);
    imgLabelRight_ = new QLabel(this);
    /*  QMainWindow possède son propre layout qui lui permet de disposer les barres d'outils
        On est donc obligé de créer un widget qui contiendra le layout du contenu de la fenêtre
        getCentralWidget() pour récupèrer ce widget
    */
    QWidget *central = new QWidget(this);
    layout_ = new QHBoxLayout(this);
    layout_->addWidget(imgLabelLeft_);
    layout_->addWidget(imgLabelRight_);
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
        QImage* image = new QImage();
        image->load(p);
        cutImage(image);
        delete image;

        // Sous Qt5.3.2 et 5.7 -> Permet de ne pas utiliser le resize event.
        // Ne marche apparement pas chez tous.
        // Hadrien Decoudras.
        //imgLabel_->setScaledContents(true);

        //imgLabel_->setPixmap(QPixmap::fromImage(image_));
        //imgLabelLeft_->setPixmap(QPixmap::fromImage(imageLeft_));
        //imgLabelRight_->setPixmap(QPixmap::fromImage(imageRight_));
        //resizeLoadedImage();
        //drawImage(*image);
        drawImages(imageLeft_, imageRight_);
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

void MainWindow::drawImage(QImage img){
  QLabel* imgLabel = new QLabel(this);
  layout_->addWidget(imgLabel);
  imgLabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::drawImages(QImage imgLeft, QImage imgRight){
  QLabel* labelLeft = new QLabel(this);
  QLabel* labelRight = new QLabel(this);

  layout_->addWidget(labelLeft);
  layout_->addWidget(labelRight);

  labelLeft->setPixmap(QPixmap::fromImage(imgLeft));
  labelRight->setPixmap(QPixmap::fromImage(imgRight));
}
