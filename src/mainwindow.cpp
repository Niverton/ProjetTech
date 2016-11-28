#include "mainwindow.hpp"
#include "imagetools.hpp"
#include "imagewidget.hpp"

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

MainWindow::MainWindow() : QMainWindow(), drawLeft(false), drawRight(false) {
  move(QApplication::desktop()->availableGeometry().center() / 2);

  /*  QMainWindow possède son propre layout qui lui permet de disposer les barres d'outils
      On est donc obligé de créer un widget qui contiendra le layout du contenu de la fenêtre
      getCentralWidget() pour récupèrer ce widget
  */
  QWidget *central = new QWidget(this);
  QLayout *layout = new QHBoxLayout(central);
  central->setLayout(layout);
  setCentralWidget(central);

  //Ajuster le taille de la fenêtre en fonction de la taille de l'image.
  adjustSize();
  //
  initMenuBar();

  imageLeft = new ImageWidget(this);
  imageRight = new ImageWidget(this);
  layout->addWidget(imageLeft);
  layout->addWidget(imageRight);
}

MainWindow::~MainWindow() {}

void MainWindow::initMenuBar() {
    QMenuBar* mBar = menuBar();

    //File
    QMenu* menuFile = new QMenu("&Fichier", mBar);
    //File - Open
    QAction* openAction = new QAction("&Ouvrir", menuFile);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menuFile->addAction(openAction);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    //File - Quit
    QAction* quitAction = new QAction("&Quitter", menuFile);
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    menuFile->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));

    //Edit
    QMenu* menuEdit = new QMenu("&Editer", mBar);
    //Edit - cut
    QAction* cutAction = new QAction("&Couper l'image", menuEdit);
    cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    menuEdit->addAction(cutAction);
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cutImgSlot()));
    //Edit - clipAction
    QAction* clipAction = new QAction("&Rogner l'image", menuEdit);
    clipAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    menuEdit->addAction(clipAction);
    connect(clipAction, SIGNAL(triggered(bool)), this, SLOT(clipImgSlot()));

    //OpenCV
    QMenu* menuOpenCV = new QMenu("&OpenCV", mBar);
    QAction* blurAction = new QAction("&Flouter l'image", menuOpenCV);
    menuOpenCV->addAction(blurAction);
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blurSlot()));

    QAction* sobelAction = new QAction("Appliquer &Sobel", menuOpenCV);
    menuOpenCV->addAction(sobelAction);
    connect(sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobelSlot()));

    QAction* cannyAction = new QAction("Appliquer &Canny", menuOpenCV);
    menuOpenCV->addAction(cannyAction);
    connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(cannySlot()));

    QAction* DispMapAction = new QAction("&Carte de dispatité", menuOpenCV);
    menuOpenCV->addAction(DispMapAction);
    connect(DispMapAction, SIGNAL(triggered(bool)), this, SLOT(dispMapSlot()));


    //About
    QMenu* menuAbout = new QMenu("À &Propos", mBar);
    QAction* aboutAction = new QAction("À &Propos", menuAbout);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    menuAbout->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(renderAbout()));

    mBar->addMenu(menuFile);
    mBar->addMenu(menuEdit);
    mBar->addMenu(menuOpenCV);
    mBar->addMenu(menuAbout);
}

void MainWindow::adjustSize() {
  centralWidget()->adjustSize();
  QMainWindow::adjustSize();
}

/*******
  SLOTS
*******/

void MainWindow::renderAbout() {
  QMessageBox::about(this, "A propos", "Projet technologique L3");
}
void MainWindow::openFile() {
  QString p = QFileDialog::getOpenFileName( 0, "Ouvrir", QString(), "Images (*.png *.jpg)");
                                          //this

  if(!p.isEmpty()) {
    QImage imageLoaded(p);
    ImageTools& tools = ImageTools::getInstance();
    imageLeft->setImage(tools.imageToMat(imageLoaded));
    drawLeft = true;
    drawRight = false;

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2), (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
  }
  adjustSize();
}
void MainWindow::cutImgSlot() {
  if (!drawLeft)
    return;
  cv::Mat img = imageLeft->getImage();
  ImageTools& tools = ImageTools::getInstance();  
  cv::Mat left, right;
  tools.split(img, left, right);
  imageLeft->setImage(left);
  imageRight->setImage(right); 
  centralWidget()->adjustSize();
  drawRight = true;
}
void MainWindow::clipImgSlot() {
  //TODO A voir
  centralWidget()->adjustSize();
}
void MainWindow::blurSlot() {
  if (!drawLeft)
    return;
  ImageTools& tools = ImageTools::getInstance();  
  cv::Mat img = imageLeft->getImage();
  tools.blur(img, 3);
  imageLeft->setImage(img);
  if (!drawRight)
    return;
  img = imageRight->getImage();
  tools.blur(img, 3);
  imageRight->setImage(img);
  centralWidget()->adjustSize();
}
void MainWindow::sobelSlot() {
  if (!drawLeft)
    return;
  ImageTools& tools = ImageTools::getInstance();  
  cv::Mat img = imageLeft->getImage();
  tools.sobel(img, 3, 1);
  imageLeft->setImage(img);
  if (!drawRight)
    return;
  img = imageRight->getImage();
  tools.sobel(img, 3, 1);
  imageRight->setImage(img);
  centralWidget()->adjustSize();
}
void MainWindow::cannySlot() {
  if (!drawLeft)
    return;
  ImageTools& tools = ImageTools::getInstance();  
  cv::Mat img = imageLeft->getImage();
  tools.canny(img, 3, 20, 2);
  imageLeft->setImage(img);
  if (!drawRight)
    return;
  img = imageRight->getImage();
  tools.canny(img, 3, 20, 2);
  imageRight->setImage(img);
  centralWidget()->adjustSize();
}
void MainWindow::dispMapSlot(){
  if (!drawLeft || !drawRight)
    return;
  ImageTools& tools = ImageTools::getInstance();

  cv::Mat img_droite = imageRight->getImage();
  cv::Mat img_gauche = imageLeft->getImage();

  cv::Mat disp = tools.disparityMapBM(img_gauche, img_droite); 

  imageLeft->setImage(disp);
  centralWidget()->adjustSize();
}