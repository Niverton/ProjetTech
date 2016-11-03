#include "mainwindow.h"
#include "stereowindow.h"
#include "cropwindow.h"
#include "processingwindow.h"

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
#include <QHBoxLayout>

#include <QDebug>

/**********************************************************************
 **********************************************************************
 *
 * ctor
 *
 **********************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    move(QApplication::desktop()->availableGeometry().center() / 2);

    /*  QMainWindow possède son propre layout qui lui permet de disposer les barres d'outils
        On est donc obligé de créer un widget qui contiendra le layout du contenu de la fenêtre
        getCentralWidget() pour récupèrer ce widget
    */
    QWidget *central = new QWidget(this);
    _layout = new QHBoxLayout(central);
    central->setLayout(_layout);
    setCentralWidget(central);

    //Ajuster le taille de la fenêtre en fonction de la taille de l'image.
    adjustSize();
    // Initting menu bar
    initMenuBar();

    _imgLabel= new QLabel(this);
    _layout->addWidget(_imgLabel);

    _statusLabel = new QLabel(statusBar());
    statusBar()->addWidget(_statusLabel);
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
    _menuFile = new QMenu("&Fichier", mBar);
    //File - Open
    _openAction = new QAction("&Ouvrir", _menuFile);
    _openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    _menuFile->addAction(_openAction);
    connect(_openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    //File - Quit
    _quitAction = new QAction("&Quitter", _menuFile);
    _quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _menuFile->addAction(_quitAction);
    connect(_quitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));

    //Edit
    _menuEdit = new QMenu("&Editer", mBar);
    //Edit - cut
    _cutAction = new QAction("&Couper l'image", _menuEdit);
    _cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    _menuEdit->addAction(_cutAction);
    connect(_cutAction, SIGNAL(triggered(bool)), this, SLOT(cutImgSlot()));
    //Edit - clipAction_
    _clipAction = new QAction("&Rogner l'image", _menuEdit);
    _clipAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    _menuEdit->addAction(_clipAction);
    connect(_clipAction, SIGNAL(triggered(bool)), this, SLOT(clipImgSlot()));

    //OpenCV
    _menuOpenCV = new QMenu("&OpenCV", mBar);
    _blurAction = new QAction("&Flouter l'image", _menuOpenCV);
    _menuOpenCV->addAction(_blurAction);
    connect(_blurAction, SIGNAL(triggered(bool)), this, SLOT(blurSlot()));

    _sobelAction = new QAction("Appliquer &Sobel", _menuOpenCV);
    _menuOpenCV->addAction(_sobelAction);
    connect(_sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobelSlot()));

    _cannyAction = new QAction("Appliquer &Canny", _menuOpenCV);
    _menuOpenCV->addAction(_cannyAction);
    connect(_cannyAction, SIGNAL(triggered(bool)), this, SLOT(cannySlot()));

    //About
    _menuAbout = new QMenu("À &Propos", mBar);
    _aboutAction = new QAction("À &Propos", _menuAbout);
    _aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    _menuAbout->addAction(_aboutAction);
    connect(_aboutAction, SIGNAL(triggered(bool)), this, SLOT(renderMessageBox()));

    mBar->addMenu(_menuFile);
    mBar->addMenu(_menuEdit);
    mBar->addMenu(_menuOpenCV);
    mBar->addMenu(_menuAbout);
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

    if(!_path.isEmpty())
    {
        resizeLoadedImage();
    }
}

/**********************************************************************
 **********************************************************************
 *
 * Initial Window size.
 *
 **********************************************************************/
QSize MainWindow::sizeHint() const
{
    QRect r = QApplication::desktop()->screenGeometry();
    return QSize(r.width() * 0.5f, r.height() * 0.5f);
}

/**********************************************************************
 **********************************************************************
 *
 * Loaded image.
 *
 **********************************************************************/
void MainWindow::resizeLoadedImage()
{
    QPixmap pxM = QPixmap::fromImage(_imageLoaded);
    QPixmap* pxmA = const_cast<QPixmap*>(_imgLabel->pixmap());
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
        _path = p;
        _statusLabel->setText(p);
        // timer pour virer le texte.
        _imageLoaded = QImage();
        _imageLoaded.load(p);
        _imageLoadedIsDraw = true;

        // Sous Qt5.3.2 et 5.7 -> Permet de ne pas utiliser le resize event.
        // Ne marche apparement pas chez tous.
        // Hadrien Decoudras.
        //imgLabel_->setScaledContents(true);

        _imgLabel->setPixmap(QPixmap::fromImage(_imageLoaded));
        resize(_imageLoaded.size());
        move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2), (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
    }
}

/*
*   Action cut
*/
void MainWindow::cutImgSlot(){
    if (!_imageLoadedIsDraw)
        return;
    StereoWindow *w = new StereoWindow(&_imageLoaded);
    w->show();
}

/*
 *  Action clip
 */
void MainWindow::clipImgSlot(){
    if (!_imageLoadedIsDraw)
        return;
    CropWindow *w = new CropWindow(&_imageLoaded);
    w->show();
}

void MainWindow::blurSlot(){
    if (!_imageLoadedIsDraw)
        return;
    // Leak ?
    ProcessingWindow *w = new ProcessingWindow(_imageLoaded);
    w->blur(5);
    w->show();
}

void MainWindow::sobelSlot(){
    if (!_imageLoadedIsDraw)
        return;
    ProcessingWindow *w = new ProcessingWindow(_imageLoaded);
    w->sobel(3, 1);
    w->show();
}

void MainWindow::cannySlot(){
    if (!_imageLoadedIsDraw)
        return;
    ProcessingWindow *w = new ProcessingWindow(_imageLoaded);
    w->canny(3, 20, 2);
    w->show();
}
