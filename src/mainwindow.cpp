#include "mainwindow.hpp"
#include "imagetools.hpp"

#include <QMessageBox>
#include <QMainWindow>
#include <QLabel>

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

  imageLeft = new ImageWidget(this);
  imageRight = new ImageWidget(this);
  layout->addWidget(imageLeft);
  layout->addWidget(imageRight);
  
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
    //Edit - clipAction
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

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  //TODO Implement (resize)
}

/*******
  SLOTS
*******/

void renderAbout() {
  QMessageBox::about(this, "A propos", "Projet technologique L3");
}
void openFile() {
  QString p = QFileDialog::getOpenFileName(this, "Ouvrir", QString(), "Images (*.png *.jpg)");

  if(!p.isEmpty()) {
    QImage imageLoaded(p);
    imageLeft->setImage(imageLoaded);
    drawLeft = true;

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2), (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
  }
}
void cutImgSlot() {
  //TODO A voir
}
void clipImgSlot() {
  if (!drawLeft) //Besoin que de l'image de gauche
    return;
  ImageTools tools = ImageTools.getInstance();
  cv::Mat& img = imageLeft->getImage();
  cv::Mat left, right;
  tools.split(img, left, right);
  imageLeft->setImage(left);
  imageRight->setImage(Right);  
}
void blurSlot() {
  if (!drawLeft)
    return;
  ImageTools tools = ImageTools.getInstance();
  cv::Mat img = imageLeft->getImage();
  tools.blur(img, 3);
  imageLeft->setImage(img);
  if (!drawRight)
    return;
  img = imageRight->getImage();
  tools.blur(img, 3);
  imageRight->setImage(img);
}
void sobelSlot() {
  if (!drawLeft)
    return;
  ImageTools tools = ImageTools.getInstance();
  cv::Mat img = imageLeft->getImage();
  tools.sobel(img, 3, 1);
  imageLeft->setImage(img);
  if (!drawRight)
    return;
  img = imageRight->getImage();
  tools.sobel(img, 3, 1);
  imageRight->setImage(img);
}
void cannySlot() {
  if (!drawLeft)
    return;
  ImageTools tools = ImageTools.getInstance();
  cv::Mat img = imageLeft->getImage();
  tools.canny(img, 3, 20, 2);
  imageLeft->setImage(img);
  if (!drawRight)
    return;
  img = imageRight->getImage();
  tools.canny(img, 3, 20, 2);
  imageRight->setImage(img);
}
