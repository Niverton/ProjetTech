/*!
 * \file mainwindow.cpp
 * \brief Implementation of the methods of the MainWindow class declared in the mainwindow.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#include "mainwindow.hpp"

#include "imageprocessor.hpp"
#include "stereoimagewidget.hpp"
#include "stereotransformwidget.hpp"
#include "aboutwidget.hpp"

#include <QMessageBox>
#include <QMainWindow>
#include <QLabel>
#include <QApplication>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QDesktopWidget>
#include <QScrollArea>

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
MainWindow::MainWindow() : QMainWindow(), drawLeft(false), drawRight(false)
{
    setMinimumSize(800, 600);
    setWindowTitle("Robotic Vision");

    QWidget* central = new QWidget(this);
    central->minimumSizeHint();

    QLayout* layout = new QHBoxLayout(central);
    central->setLayout(layout);
    setCentralWidget(central);

    QScrollArea* scA = new QScrollArea(this);
    QScrollArea* scB = new QScrollArea(this);
    scA->setAlignment(Qt::AlignCenter);
    scB->setAlignment(Qt::AlignCenter);

    imageLeft = new StereoImageWidget(this, 0);
    imageRight = new StereoImageWidget(this, 1);

    layout->addWidget(scA);
    layout->addWidget(scB);
    scA->setWidget(imageLeft);
    scB->setWidget(imageRight);

    layout->setAlignment(imageLeft, Qt::AlignCenter);
    layout->setAlignment(imageRight, Qt::AlignCenter);

    undoStack.setLeftWidget(imageLeft);
    undoStack.setRightWidget(imageRight);
    imageLeft->addUndoStack(&undoStack);
    imageRight->addUndoStack(&undoStack);

    initMenuBar();

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2),
         (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
MainWindow::~MainWindow() {}

/**************************************************************
 **************************************************************
 *
 * Initializes menus.
 *
 **************************************************************/
void MainWindow::initMenuBar() {
    QMenuBar* mBar = menuBar();

    //File
    QMenu* menuFile = new QMenu("&File", mBar);

    //File - Open
    QAction* openAction = new QAction("&Open", menuFile);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menuFile->addAction(openAction);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));

    //File - Quit
    QAction* quitAction = new QAction("&Quit", menuFile);
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    menuFile->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));

    //Edit
    QMenu* menuEdit = new QMenu("&Edit", mBar);

    //Edit - undo
    QAction* undoAction = new QAction("&Undo", menuEdit);
    undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    menuEdit->addAction(undoAction);
    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(undo()));

    //Edit - cut
    QAction* cutAction = new QAction("&Split", menuEdit);
    cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    menuEdit->addAction(cutAction);
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cut()));

    //Edit - clipAction
    QAction* clipAction = new QAction("&Crop", menuEdit);
    clipAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    menuEdit->addAction(clipAction);
    connect(clipAction, SIGNAL(triggered(bool)), this, SLOT(clip()));

    // View
    QMenu* menuView = new QMenu("&View", mBar);

    // View - Left ZoomIn
    QAction* zoomInLeftAction = new QAction("&Left Zoom-In", menuView);
    menuView->addAction(zoomInLeftAction);
    connect(zoomInLeftAction, SIGNAL(triggered(bool)), imageLeft, SLOT(zoomIn()));

    // View - Right ZoomIn
    QAction* zoomInRightAction = new QAction("&Right Zoom-In", menuView);
    menuView->addAction(zoomInRightAction);
    connect(zoomInRightAction, SIGNAL(triggered(bool)), imageRight, SLOT(zoomIn()));

    // View - Left ZoomOut
    QAction* zoomOutLeftAction = new QAction("&Left Zoom-Out", menuView);
    menuView->addAction(zoomOutLeftAction);
    connect(zoomOutLeftAction, SIGNAL(triggered(bool)), imageLeft, SLOT(zoomOut()));

    // View - Right ZoomOut
    QAction* zoomOutRightAction = new QAction("&Right Zoom-Out", menuView);
    menuView->addAction(zoomOutRightAction);
    connect(zoomOutRightAction, SIGNAL(triggered(bool)), imageRight, SLOT(zoomOut()));

    //OpenCV
    QMenu* menuOpenCV = new QMenu("&OpenCV", mBar);

    QAction* blurAction = new QAction("&Blur", menuOpenCV);
    blurAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_B));
    menuOpenCV->addAction(blurAction);
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blur()));

    QAction* sobelAction = new QAction("&Sobel", menuOpenCV);
    sobelAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_S));
    menuOpenCV->addAction(sobelAction);
    connect(sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobel()));

    QAction* cannyAction = new QAction("&Canny", menuOpenCV);
    cannyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_C));
    menuOpenCV->addAction(cannyAction);
    connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(canny()));

    QAction* dispMapAction = new QAction("&Disparity map", menuOpenCV);
    menuOpenCV->addAction(dispMapAction);
    connect(dispMapAction, SIGNAL(triggered(bool)), this, SLOT(disparity()));
/*
    QAction* DepthMapAction = new QAction("&Depth map", menuOpenCV);
    menuOpenCV->addAction(DepthMapAction);
    connect(DepthMapAction, SIGNAL(triggered(bool)), this, SLOT(depthMapSlot()));
*/
    //About
    QMenu* menuAbout = new QMenu("&Help", mBar);
    QAction* aboutAction = new QAction("&About", menuAbout);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    menuAbout->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

#if NON_FREE == 1
    QAction* flannAction = new QAction("&Algorithme de flann (avec surf)", menuOpenCV);
    menuOpenCV->addAction(flannAction);
    connect(flannAction, SIGNAL(triggered(bool)), this, SLOT(flannSlot()));
#endif

    mBar->addMenu(menuFile);
    mBar->addMenu(menuEdit);
    mBar->addMenu(menuView);
    mBar->addMenu(menuOpenCV);
    mBar->addMenu(menuAbout);
}

/**************************************************************
 **************************************************************
 *
 * Displays about.
 *
 **************************************************************/
void MainWindow::about()
{
    aboutWidget = new AboutWidget("<div align='center'>"
                                    "<b>Projet Technologique</b><br/>"
                                    "<b>Licence 3 Informatique</b><br/>"
                                    "<b>Université Bordeaux I</b><br/><br/>"
                                    "<i>Jérémi Bernard</i><br/>"
                                    "<i>Benjamin De Pourquery</i><br/>"
                                    "<i>Rémy Maugey</i><br/>"
                                    "<i>Hadrien Decoudras</i><br/><br/>"
                                    "<i>2016-2017</i><br/>"
                                  "</div>");
    aboutWidget->show();
}

/**************************************************************
 **************************************************************
 *
 * Opens image.
 *
 **************************************************************/
void MainWindow::open()
{
    QString p = QFileDialog::getOpenFileName(nullptr, "Ouvrir", QString(), "Images (*.png *.jpg)");

    if(!p.isEmpty())
    {
        QImage imageLoaded(p);
        ImageProcessor& tools = ImageProcessor::Instance();
        imageLeft->setImage(tools.imageToCvMat(imageLoaded));

        cv::Mat empty;
        imageRight->setImage(empty);

        drawLeft = true;
        drawRight = false;
    }
}

/**************************************************************
 **************************************************************
 *
 * Undo stack.
 *
 **************************************************************/
void MainWindow::undo()
{
    undoStack.undo();
}

/**************************************************************
 **************************************************************
 *
 * Cuts image.
 *
 **************************************************************/
void MainWindow::cut()
{
    if(!drawLeft)
    {
        return;
    }

    cv::Mat lImg = imageLeft->getImage();
    cv::Mat rImg = imageRight->getImage();

    undoStack.pushLeft(lImg);
    undoStack.pushRight(rImg);

    ImageProcessor& tools = ImageProcessor::Instance();
    cv::Mat left, right;

    tools.split(lImg, left, right);

    imageLeft->setImage(left);
    imageRight->setImage(right);

    drawRight = true;
}

/**************************************************************
 **************************************************************
 *
 * Clips image.
 *
 **************************************************************/
void MainWindow::clip()
{

}

/**************************************************************
 **************************************************************
 *
 * Blur.
 *
 **************************************************************/
void MainWindow::blur()
{
    if(!drawLeft)
    {
        return;
    }

    ImageProcessor& tools = ImageProcessor::Instance();
    cv::Mat img = imageLeft->getImage();

    undoStack.pushLeft(img);

    tools.blur(img, 3);
    imageLeft->setImage(img);

    if(!drawRight)
    {
        return;
    }

    img = imageRight->getImage();

    undoStack.pushRight(img);

    tools.blur(img, 3);
    imageRight->setImage(img);
}

/**************************************************************
 **************************************************************
 *
 * Sobel.
 *
 **************************************************************/
void MainWindow::sobel()
{
    if(!drawLeft)
    {
        return;
    }

    ImageProcessor& tools = ImageProcessor::Instance();
    cv::Mat img = imageLeft->getImage();

    undoStack.pushLeft(img);

    tools.sobel(img, 3, 1);
    imageLeft->setImage(img);

    if(!drawRight)
    {
        return;
    }

    img = imageRight->getImage();

    undoStack.pushRight(img);

    tools.sobel(img, 3, 1);
    imageRight->setImage(img);
}

/**************************************************************
 **************************************************************
 *
 * Canny.
 *
 **************************************************************/
void MainWindow::canny()
{
    if(!drawLeft)
    {
        return;
    }

    ImageProcessor& tools = ImageProcessor::Instance();
    cv::Mat img = imageLeft->getImage();

    undoStack.pushLeft(img);

    tools.canny(img, 3, 20, 2);
    imageLeft->setImage(img);

    if(!drawRight)
    {
        return;
    }

    img = imageRight->getImage();

    undoStack.pushRight(img);

    tools.canny(img, 3, 20, 2);
    imageRight->setImage(img);
}

/**************************************************************
 **************************************************************
 *
 * Disparity map.
 *
 **************************************************************/
void MainWindow::disparity()
{
    if (!drawLeft || !drawRight)
    {
        return;
    }

    ImageProcessor& tools = ImageProcessor::Instance();

    cv::Mat rImage = imageRight->getImage();
    cv::Mat lImage = imageLeft->getImage();

    cv::Mat disp = tools.disparityMap(lImage, rImage, ImageProcessor::StereoMode::STEREO_MODE_SGBM);

    transformWidget = new StereoTransformWidget(disp, "Disparity map");
    transformWidget->show();
}

/*
void MainWindow::depthMapSlot(){
    if (!drawLeft || !drawRight)
      return;
    ImageTools& tools = ImageTools::getInstance();
}
*/

/**************************************************************
 **************************************************************
 *
 * Flann.
 *
 **************************************************************/
void MainWindow::flann(){
  #if NON_FREE == 1
    if (!drawLeft || !drawRight)
      return;
    ImageTools& tools = ImageTools::getInstance();

    cv::Mat img_gauche = imageLeft->getImage();
    cv::Mat img_droite = imageRight->getImage();

    cv::Mat disp = tools.flann(img_gauche, img_droite);

    cv::Mat empty;
    /*imageLeft->setImage(disp);
    imageRight->setImage(empty);*/
    changeImages(disp, empty);
    centralWidget()->adjustSize();
  #endif
  #if NON_FREE == 0
    QMessageBox::about(this, "Erreur", "Impossible de charger le module non free");
    return;
  #endif
}
