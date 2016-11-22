#include "mainwindow.hpp"

MainWindow::MainWindow() : QMainWindow(), drawLeft(false), drawRight(false) {
  move(QApplication::desktop()->availableGeometry().center() / 2);

  /*  QMainWindow possède son propre layout qui lui permet de disposer les barres d'outils
      On est donc obligé de créer un widget qui contiendra le layout du contenu de la fenêtre
      getCentralWidget() pour récupèrer ce widget
  */
  QWidget *central = new QWidget(this);
  QLayout *layout = new QHBoxLayout(central);
  central->setLayout(*layout);
  setCentralWidget(central);

  //Ajuster le taille de la fenêtre en fonction de la taille de l'image.
  adjustSize();
  //
  initMenuBar();

  imageLeft = new QLabel(this);
  imageDroite = new QLabel(this);
  
  layout->addWidget(imageLeft);
  layout->addWidget(imageDroite);
  
}

MainWindow::~MainWindow() {}

void MainWindow::initMenuBar() {
    QMenuBar* mBar = menuBar();

    //File
    QMenu menuFile = new QMenu("&Fichier", mBar);
    //File - Open
    QAction openAction = new QAction("&Ouvrir", menuFile);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menuFile->addAction(openAction);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    //File - Quit
    QAction quitAction = new QAction("&Quitter", menuFile);
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    menuFile->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));

    //Edit
    QMenu menuEdit = new QMenu("&Editer", mBar);
    //Edit - cut
    QAction cutAction = new QAction("&Couper l'image", menuEdit);
    cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    menuEdit->addAction(cutAction);
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cutImgSlot()));
    //Edit - clipAction_
    QAction clipAction = new QAction("&Rogner l'image", menuEdit);
    clipAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    menuEdit->addAction(clipAction);
    connect(clipAction, SIGNAL(triggered(bool)), this, SLOT(clipImgSlot()));

    //OpenCV
    QMenu menuOpenCV = new QMenu("&OpenCV", mBar);
    QAction blurAction = new QAction("&Flouter l'image", menuOpenCV);
    menuOpenCV->addAction(blurAction);
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blurSlot()));

    QAction sobelAction = new QAction("Appliquer &Sobel", menuOpenCV);
    menuOpenCV->addAction(sobelAction);
    connect(sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobelSlot()));

    QAction cannyAction = new QAction("Appliquer &Canny", menuOpenCV);
    menuOpenCV->addAction(cannyAction);
    connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(cannySlot()));

    //About
    QMenu menuAbout = new QMenu("À &Propos", mBar);
    QAction aboutAction = new QAction("À &Propos", menuAbout);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    menuAbout->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(renderAbout()));

    mBar->addMenu(menuFile);
    mBar->addMenu(menuEdit);
    mBar->addMenu(menuOpenCV);
    mBar->addMenu(menuAbout);
}

/*******
  FOO
*******/

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   //TODO Implement (resize)
}

void MainWindow::updateImages() {
  //TODO Implement updateImages
}

/*******
  SLOTS
*******/

void renderAbout() {
  //TODO Implement renderAbout
}
void openFile() {
  //TODO Implement openFile
}
void cutImgSlot() {
  //TODO Implement cutImgSlot
}
void clipImgSlot() {
  //TODO Implement clipImgSlot
}
void blurSlot() {
  //TODO Implement blurSlot
}
void sobelSlot() {
  //TODO Implement sobelSlot
}
void cannySlot() {
  //TODO Implement cannySlot
}
