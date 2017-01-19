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
  central->minimumSizeHint();
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

  layout->setAlignment(imageLeft, Qt::AlignCenter);
  layout->setAlignment(imageRight, Qt::AlignCenter);

  undoStack.setLeftWidget(imageLeft);
  undoStack.setRightWidget(imageRight);
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

    //Edit - undo
    QAction* undoAction = new QAction("&Undo", menuEdit);
    undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    menuEdit->addAction(undoAction);
    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(undoSlot()));

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
    blurAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_B));
    menuOpenCV->addAction(blurAction);
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blurSlot()));

    QAction* sobelAction = new QAction("Appliquer &Sobel", menuOpenCV);
    sobelAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_S));
    menuOpenCV->addAction(sobelAction);
    connect(sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobelSlot()));

    QAction* cannyAction = new QAction("Appliquer &Canny", menuOpenCV);
    cannyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_C));
    menuOpenCV->addAction(cannyAction);
    connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(cannySlot()));

    QAction* dispMapAction = new QAction("&Carte de dispatité", menuOpenCV);
    menuOpenCV->addAction(dispMapAction);
    connect(dispMapAction, SIGNAL(triggered(bool)), this, SLOT(dispMapSlot()));
/*
    QAction* DepthMapAction = new QAction("&Carte de profondeur", menuOpenCV);
    menuOpenCV->addAction(DepthMapAction);
    connect(DepthMapAction, SIGNAL(triggered(bool)), this, SLOT(depthMapSlot()));
*/
    //About
    QMenu* menuAbout = new QMenu("À &Propos", mBar);
    QAction* aboutAction = new QAction("À &Propos", menuAbout);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    menuAbout->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(renderAbout()));

#if NON_FREE == 1
    QAction* flannAction = new QAction("&Algorithme de flann (avec surf)", menuOpenCV);
    menuOpenCV->addAction(flannAction);
    connect(flannAction, SIGNAL(triggered(bool)), this, SLOT(flannSlot()));
#endif

    mBar->addMenu(menuFile);
    mBar->addMenu(menuEdit);
    mBar->addMenu(menuOpenCV);
    mBar->addMenu(menuAbout);
}

void MainWindow::adjustSize() {
  centralWidget()->adjustSize();
  centralWidget()->minimumSizeHint();
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

    cv::Mat empty;
    imageRight->setImage(empty);
    //changeImages(img, empty);
    drawLeft = true;
    drawRight = false;

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2), (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
  }
  adjustSize();
}

void MainWindow::undoSlot() {
    /*if (undoStackLeft.empty() || undoStackRight.empty())
        return;

    imageLeft->setImage(undoStackLeft.top());
    undoStackLeft.pop();
    imageRight->setImage(undoStackRight.top());
    undoStackRight.pop();*/
    undoStack.undo();
}

void MainWindow::cutImgSlot() {
    if (!drawLeft)
        return;

    cv::Mat lImg = imageLeft->getImage();
    cv::Mat rImg = imageRight->getImage();

    undoStack.pushLeft(lImg);
    undoStack.pushRight(rImg);

    ImageTools& tools = ImageTools::getInstance();
    cv::Mat left, right;

    tools.split(lImg, left, right);

    imageLeft->setImage(left);
    imageRight->setImage(right);

    centralWidget()->adjustSize();
    drawRight = true;
}

void MainWindow::clipImgSlot() {
  //TODO A voir toggle fonction sur les widgets
  centralWidget()->adjustSize();
}

void MainWindow::blurSlot() {
    if (!drawLeft)
        return;

    ImageTools& tools = ImageTools::getInstance();
    cv::Mat img = imageLeft->getImage();

    undoStack.pushLeft(img);

    tools.blur(img, 3);
    imageLeft->setImage(img);

    if (!drawRight)
        return;

    img = imageRight->getImage();

    undoStack.pushRight(img);

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
  //imageLeft->setImage(img);
  if (!drawRight)
    return;
  cv::Mat img2 = imageRight->getImage();
  tools.sobel(img2, 3, 1);
  //imageRight->setImage(img);
  //changeImages(img, img2);
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

  cv::Mat img2 = imageRight->getImage();
  tools.canny(img2, 3, 20, 2);
  imageRight->setImage(img);
  //changeImages(img, img2);
  centralWidget()->adjustSize();
}
void MainWindow::dispMapSlot(){
  if (!drawLeft || !drawRight)
    return;

  ImageTools& tools = ImageTools::getInstance();

  cv::Mat img_droite = imageRight->getImage();
  cv::Mat img_gauche = imageLeft->getImage();

  cv::Mat disp = tools.disparityMap(img_gauche, img_droite, ImageTools::STEREO_SGBM); 

  cv::Mat empty;
  imageLeft->setImage(disp);
  imageRight->setImage(empty);

  centralWidget()->adjustSize();
}

/*
void MainWindow::depthMapSlot(){
    if (!drawLeft || !drawRight)
      return;
    ImageTools& tools = ImageTools::getInstance();
}
*/

void MainWindow::flannSlot(){
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

