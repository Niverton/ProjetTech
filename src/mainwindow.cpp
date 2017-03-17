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

#include "processors/imageprocessor.hpp"

#include "widgets/images/imagecropwidget.hpp"
#include "widgets/images/stereoimageswidget.hpp"
#include "widgets/images/stereotransformwidget.hpp"
#include "widgets/parametersdockwidget.hpp"
#include "widgets/cudagpuinfowidget.hpp"
#include "widgets/aboutwidget.hpp"
#include "widgets/mainstatusbarwidget.hpp"
#include "widgets/videos/videowidget.hpp"

#include "parameters/blurparameters.hpp"
#include "parameters/sobelparameters.hpp"
#include "parameters/cannyparameters.hpp"
#include "parameters/disparitymapparameters.hpp"
#include "parameters/parameterobservers.hpp"

#include "utils/cudartgpuinfodl.hpp"

#include "except/parametersdockwidgetgeneratorexception.hpp"
#include "except/cudartnotfoundexception.hpp"
#include "except/cudartresolveexception.hpp"

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

#include <QDebug>

#include <chrono>

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
MainWindow::MainWindow() : QMainWindow(), parametersDockWidget(nullptr)
{
    setMinimumSize(800, 600);
    setWindowTitle("Robotic Vision");

    QFile file(":/styles/mainstatusbarwidget/mainstatusbarwidget.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = file.readAll();
    setStyleSheet(styleSheet);
    file.close();

    stereoWidget = new StereoImagesWidget(this);
    setCentralWidget(stereoWidget);

    appStates.setInitialImages(stereoWidget->getLeftImageWidget(), stereoWidget->getRighImageWidget());

    stereoWidget->getLeftImageWidget()->attachApplicationStates(&appStates);
    stereoWidget->getRighImageWidget()->attachApplicationStates(&appStates);

    initMenuBar();

    observers = new ParameterObservers({
                        ParameterObservers::Observer::OBS_BLUR,
                        ParameterObservers::Observer::OBS_SOBEL,
                        ParameterObservers::Observer::OBS_CANNY,
                        ParameterObservers::Observer::OBS_DISPARITY
                    });

    leftStatusBarWidget = new MainStatusBarLeftWidget("Ready", statusBar());
    statusBar()->addWidget(leftStatusBarWidget);

    rightStatusBarWidget = new MainStatusBarRightWidget();
    statusBar()->addPermanentWidget(rightStatusBarWidget);

    cudaRunTimeLibraryDetected = CudaRTGPUInfoDL::cudaRunTimeDetected();

    connect(stereoWidget->getLeftImageWidget(), SIGNAL(coordinatesChanged(const QPoint&)), rightStatusBarWidget, SLOT(updateStereoLeftCoordinates(const QPoint&)));
    connect(stereoWidget->getRighImageWidget(), SIGNAL(coordinatesChanged(const QPoint&)), rightStatusBarWidget, SLOT(updateStereoRightCoordinates(const QPoint&)));

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2),
         (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
MainWindow::~MainWindow()
{
    delete observers;
}

/**************************************************************
 **************************************************************
 *
 * Initializes menus.
 *
 **************************************************************/
void MainWindow::initMenuBar()
{
    QMenuBar* mBar = menuBar();

    // File.
    QMenu* menuFile = new QMenu("&File", mBar);

    // File - Open.
    QAction* openAction = new QAction("&Open", menuFile);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menuFile->addAction(openAction);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));

    // File - Quit.
    QAction* quitAction = new QAction("&Quit", menuFile);
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    menuFile->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));

    // Edit.
    QMenu* menuEdit = new QMenu("&Edit", mBar);

    // Edit - undo.
    QAction* undoAction = new QAction("&Undo", menuEdit);
    undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    menuEdit->addAction(undoAction);
    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(undo()));

    // Edit - cut.
    QAction* cutAction = new QAction("&Split", menuEdit);
    cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    menuEdit->addAction(cutAction);
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cut()));

    // Edit - clipAction.
    QAction* clipAction = new QAction("&Crop", menuEdit);
    clipAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    menuEdit->addAction(clipAction);
    connect(clipAction, SIGNAL(triggered(bool)), this, SLOT(clip()));

    // View.
    QMenu* menuView = new QMenu("&View", mBar);

    // View - Left ZoomIn.
    QAction* zoomInLeftAction = new QAction("&Left Zoom-In", menuView);
    menuView->addAction(zoomInLeftAction);
    connect(zoomInLeftAction, SIGNAL(triggered(bool)), stereoWidget->getLeftImageWidget(), SLOT(zoomIn()));

    // View - Right ZoomIn.
    QAction* zoomInRightAction = new QAction("&Right Zoom-In", menuView);
    menuView->addAction(zoomInRightAction);
    connect(zoomInRightAction, SIGNAL(triggered(bool)), stereoWidget->getRighImageWidget(), SLOT(zoomIn()));

    // View - Left ZoomOut.
    QAction* zoomOutLeftAction = new QAction("&Left Zoom-Out", menuView);
    menuView->addAction(zoomOutLeftAction);
    connect(zoomOutLeftAction, SIGNAL(triggered(bool)), stereoWidget->getLeftImageWidget(), SLOT(zoomOut()));

    // View - Right ZoomOut.
    QAction* zoomOutRightAction = new QAction("&Right Zoom-Out", menuView);
    menuView->addAction(zoomOutRightAction);
    connect(zoomOutRightAction, SIGNAL(triggered(bool)), stereoWidget->getRighImageWidget(), SLOT(zoomOut()));

    // OpenCV.
    QMenu* menuOpenCV = new QMenu("&OpenCV", mBar);

    // OpenCV - Blur.
    QAction* blurAction = new QAction("&Blur", menuOpenCV);
    blurAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_B));
    menuOpenCV->addAction(blurAction);
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blurMenuClicked()));
    //connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blur()));

    // OpenCV - Sobel.
    QAction* sobelAction = new QAction("&Sobel", menuOpenCV);
    sobelAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_S));
    menuOpenCV->addAction(sobelAction);
    connect(sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobelMenuClicked()));
    //connect(sobelAction, SIGNAL(triggered(bool)), this, SLOT(sobel()));

    // OpenCV - Canny.
    QAction* cannyAction = new QAction("&Canny", menuOpenCV);
    cannyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_C));
    menuOpenCV->addAction(cannyAction);
    connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(cannyMenuClicked()));
    //connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(canny()));

    // OpenCV - Disparity.
    QAction* dispMapAction = new QAction("&Disparity map", menuOpenCV);
    menuOpenCV->addAction(dispMapAction);
    connect(dispMapAction, SIGNAL(triggered(bool)), this, SLOT(disparityMenuClicked()));
    //connect(dispMapAction, SIGNAL(triggered(bool)), this, SLOT(disparity()));

    // OpenCV - FLANN.
    QAction* flannAction = new QAction("&FLANN", menuOpenCV);
    menuOpenCV->addAction(flannAction);
    connect(flannAction, SIGNAL(triggered(bool)), this, SLOT(flann()));

    /*
    QAction* depthMapAction = new QAction("&Depth map", menuOpenCV);
    menuOpenCV->addAction(depthMapAction);
    connect(depthMapAction, SIGNAL(triggered(bool)), this, SLOT(depth()));
    */

    // Help.
    QMenu* menuAbout = new QMenu("&Help", mBar);

    // Help - GPU Info.
    QAction* gpuIndoAction = new QAction("&Cuda", menuAbout);
    gpuIndoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_G));
    menuAbout->addAction(gpuIndoAction);
    connect(gpuIndoAction, SIGNAL(triggered(bool)), this, SLOT(gpuInfo()));

    // Help - About.
    QAction* aboutAction = new QAction("&About", menuAbout);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
    menuAbout->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

    mBar->addMenu(menuFile);
    mBar->addMenu(menuEdit);
    mBar->addMenu(menuView);
    mBar->addMenu(menuOpenCV);
    mBar->addMenu(menuAbout);
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
        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat image = ip.imageToCvMat(imageLoaded);
        stereoWidget->getLeftImageWidget()->setImage(image);
        appStates.setInitialLeftStereoImage(stereoWidget->getLeftImageWidget());

        emit leftStatusBarWidget->updateNotification("Open: " + p, MainStatusBarLeftWidget::STYLE_VALID);
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
    appStates.reverse(ApplicationStates::States::STATE_PREVIOUS);
}

void MainWindow::saveStereoTransitoryStates(bool value)
{
    if(value)
    {
        appStates.setTransitoryImages(stereoWidget->getLeftImageWidget(), stereoWidget->getRighImageWidget());
        appStates.lockTransitoryState(true);
    }
    else
    {
        appStates.lockTransitoryState(false);
    }
}

/**************************************************************
 **************************************************************
 *
 * Cuts image.
 *
 **************************************************************/
void MainWindow::cut()
{
    if(!stereoWidget->getLeftImageWidget()->hasImage())
    {
        QMessageBox::warning(this, "No loaded image!", "Please, load an image through\nthe 'open' entry of the 'File' menu.");
        return;
    }

    cv::Mat lImg = stereoWidget->getLeftImageWidget()->getImage();

    ImageProcessor& ip = ImageProcessor::Instance();
    cv::Mat left;
    cv::Mat right;

    ip.split(lImg, left, right);

    stereoWidget->getLeftImageWidget()->setImage(left);
    stereoWidget->getRighImageWidget()->setImage(right);
    appStates.setInitialStereoImages(stereoWidget->getLeftImageWidget(), stereoWidget->getRighImageWidget());
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
 * Generates blur dockwidget content.
 *
 **************************************************************/
void MainWindow::blurMenuClicked()
{
    if(!stereoWidget->getLeftImageWidget()->hasImage())
    {
        QMessageBox::warning(this, "No loaded image!", "Please, load an image through\nthe 'open' entry of the 'File' menu.");
        return;
    }

    try
    {
        if(parametersDockWidget)
        {
            if(parametersDockWidget->hasBeenGenerated())
            {
                parametersDockWidget->disconnect();
            }
        }

        generateParametersDockWidget();
        emit method(static_cast<int>(ParametersDockWidget::Generator::GEN_BLUR));
        connect(parametersDockWidget, SIGNAL(applyButtonClicked()), this, SLOT(blur()));
        connect(parametersDockWidget, SIGNAL(valuesChanged()), this, SLOT(blurRealTime()));
        connect(parametersDockWidget, SIGNAL(realTimeCheckBoxChecked(bool)), this, SLOT(saveStereoTransitoryStates(bool)));
    }
    catch(const ParametersDockWidgetGeneratorException& e)
    {
        QMessageBox::critical(this, "Dock Widget Generation Failure!", QString(e.what()));
    }
}

/**************************************************************
 **************************************************************
 *
 * Generates sobel dockwidget content.
 *
 **************************************************************/
void MainWindow::sobelMenuClicked()
{
    if(!stereoWidget->getLeftImageWidget()->hasImage())
    {
        QMessageBox::warning(this, "No loaded image!", "Please, load an image through\nthe 'open' entry of the 'File' menu.");
        return;
    }

    try
    {
        if(parametersDockWidget)
        {
            if(parametersDockWidget->hasBeenGenerated())
            {
                parametersDockWidget->disconnect();
            }
        }

        generateParametersDockWidget();
        emit method(static_cast<int>(ParametersDockWidget::Generator::GEN_SOBEL));
        connect(parametersDockWidget, SIGNAL(applyButtonClicked()), this, SLOT(sobel()));
        connect(parametersDockWidget, SIGNAL(valuesChanged()), this, SLOT(sobelRealTime()));
        connect(parametersDockWidget, SIGNAL(realTimeCheckBoxChecked(bool)), this, SLOT(saveStereoTransitoryStates(bool)));
    }
    catch(const ParametersDockWidgetGeneratorException& e)
    {
        QMessageBox::critical(this, "Dock Widget Generation Failure!", QString(e.what()));
    }
}

/**************************************************************
 **************************************************************
 *
 * Generates canny dockwidget content.
 *
 **************************************************************/
void MainWindow::cannyMenuClicked()
{
    if(!stereoWidget->getLeftImageWidget()->hasImage())
    {
        QMessageBox::warning(this, "No loaded image!", "Please, load an image through\nthe 'open' entry of the 'File' menu.");
        return;
    }

    try
    {
        if(parametersDockWidget)
        {
            if(parametersDockWidget->hasBeenGenerated())
            {
                parametersDockWidget->disconnect();
            }
        }

        generateParametersDockWidget();
        emit method(static_cast<int>(ParametersDockWidget::Generator::GEN_CANNY));
        connect(parametersDockWidget, SIGNAL(applyButtonClicked()), this, SLOT(canny()));
        connect(parametersDockWidget, SIGNAL(valuesChanged()), this, SLOT(cannyRealTime()));
        connect(parametersDockWidget, SIGNAL(realTimeCheckBoxChecked(bool)), this, SLOT(saveStereoTransitoryStates(bool)));
    }
    catch(const ParametersDockWidgetGeneratorException& e)
    {
        QMessageBox::critical(this, "Dock Widget Generation Failure!", QString(e.what()));
    }
}

/**************************************************************
 **************************************************************
 *
 * Generates disparity map dockwidget content.
 *
 **************************************************************/
void MainWindow::disparityMenuClicked()
{
    if(!stereoWidget->getLeftImageWidget()->hasImage())
    {
        QMessageBox::warning(this, "No loaded image!", "Please, load an image through\nthe 'open' entry of the 'File' menu.");
        return;
    }

    try
    {
        if(parametersDockWidget)
        {
            if(parametersDockWidget->hasBeenGenerated())
            {
                parametersDockWidget->disconnect();
            }
        }

        generateParametersDockWidget();
        emit method(static_cast<int>(ParametersDockWidget::Generator::GEN_DISPARITY));
        connect(parametersDockWidget, SIGNAL(applyButtonClicked()), this, SLOT(disparity()));
        connect(parametersDockWidget, SIGNAL(valuesChanged()), this, SLOT(disparityRealTime()));
        connect(parametersDockWidget, SIGNAL(realTimeCheckBoxChecked(bool)), this, SLOT(saveStereoTransitoryStates(bool)));
    }
    catch(const ParametersDockWidgetGeneratorException& e)
    {
        QMessageBox::critical(this, "Dock Widget Generation Failure!", QString(e.what()));
    }
}

/**************************************************************
 **************************************************************
 *
 * Blur.
 *
 **************************************************************/
void MainWindow::blur()
{
    BlurParameters* bp = static_cast<BlurParameters*>(observers->getObserver(ParameterObservers::Observer::OBS_BLUR));

    if(!bp->getRealTime())
    {
        appStates.store();

        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();

        ip.blur(left, bp->getKSizeW(), bp->getKSizeH());
        stereoWidget->getLeftImageWidget()->setImage(left);

        if(!stereoWidget->getRighImageWidget()->hasImage())
        {
            return;
        }

        cv::Mat right = stereoWidget->getRighImageWidget()->getImage();

        ip.blur(right, bp->getKSizeW(), bp->getKSizeH());
        stereoWidget->getRighImageWidget()->setImage(right);
    }
}

/**************************************************************
 **************************************************************
 *
 * Blur real time.
 *
 **************************************************************/
void MainWindow::blurRealTime()
{
    BlurParameters* bp = static_cast<BlurParameters*>(observers->getObserver(ParameterObservers::Observer::OBS_BLUR));

    if(bp->getRealTime())
    {
        appStates.reverse(ApplicationStates::States::STATE_TRANSITORY);

        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();

        ip.blur(left, bp->getKSizeW(), bp->getKSizeH());
        stereoWidget->getLeftImageWidget()->setImage(left);


        if(!stereoWidget->getRighImageWidget()->hasImage())
        {
            return;
        }

        cv::Mat right = stereoWidget->getRighImageWidget()->getImage();

        ip.blur(right, bp->getKSizeW(), bp->getKSizeH());
        stereoWidget->getRighImageWidget()->setImage(right);
    }
}

/**************************************************************
 **************************************************************
 *
 * Sobel.
 *
 **************************************************************/
void MainWindow::sobel()
{
    SobelParameters* sp = static_cast<SobelParameters*>(observers->getObserver(ParameterObservers::Observer::OBS_SOBEL));

    if(!sp->getRealTime())
    {
        appStates.store();

        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();

        try
        {
            ip.sobel(left, left.depth(), sp->getDx(), sp->getDy(), sp->getKSize(), sp->getScale(), sp->getDelta());
        }
        catch(const cv::Exception& e)
        {
            emit leftStatusBarWidget->updateNotification("OpenCV Error: " + QString::fromStdString(e.err), MainStatusBarLeftWidget::STYLE_INVALID);
            appStates.reverse(ApplicationStates::States::STATE_PREVIOUS);
            return;
        }


        emit leftStatusBarWidget->updateNotification("Sobel filter applied!", MainStatusBarLeftWidget::STYLE_VALID);

        stereoWidget->getLeftImageWidget()->setImage(left);

        if(!stereoWidget->getRighImageWidget()->hasImage())
        {
            return;
        }

        cv::Mat right = stereoWidget->getRighImageWidget()->getImage();

        ip.sobel(right, right.depth(), sp->getDx(), sp->getDy(), sp->getKSize(), sp->getScale(), sp->getDelta());
        stereoWidget->getRighImageWidget()->setImage(right);
    }
}

/**************************************************************
 **************************************************************
 *
 * Sobel real time.
 *
 **************************************************************/
void MainWindow::sobelRealTime()
{
    SobelParameters* sp = static_cast<SobelParameters*>(observers->getObserver(ParameterObservers::Observer::OBS_SOBEL));

    if(sp->getRealTime())
    {
        appStates.reverse(ApplicationStates::States::STATE_TRANSITORY);

        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();

        try
        {
            ip.sobel(left, left.depth(), sp->getDx(), sp->getDy(), sp->getKSize(), sp->getScale(), sp->getDelta());
        }
        catch(const cv::Exception& e)
        {
            emit leftStatusBarWidget->updateNotification("OpenCV Error: " + QString::fromStdString(e.err), MainStatusBarLeftWidget::STYLE_INVALID);
            appStates.reverse(ApplicationStates::States::STATE_PREVIOUS);
            return;
        }

        emit leftStatusBarWidget->updateNotification("Sobel filter applied!", MainStatusBarLeftWidget::STYLE_VALID);

        stereoWidget->getLeftImageWidget()->setImage(left);

        if(!stereoWidget->getRighImageWidget()->hasImage())
        {
            return;
        }

        cv::Mat right = stereoWidget->getRighImageWidget()->getImage();

        ip.sobel(right, right.depth(), sp->getDx(), sp->getDy(), sp->getKSize(), sp->getScale(), sp->getDelta());
        stereoWidget->getRighImageWidget()->setImage(right);
    }
}

/**************************************************************
 **************************************************************
 *
 * Canny.
 *
 **************************************************************/
void MainWindow::canny()
{
    CannyParameters* cp = static_cast<CannyParameters*>(observers->getObserver(ParameterObservers::Observer::OBS_CANNY));

    if(!cp->getRealTime())
    {
        appStates.store();

        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();

        ip.canny(left, cp->getHThrA(), cp->getHThrB(), cp->getAperture(), cp->getGMagnitude());
        stereoWidget->getLeftImageWidget()->setImage(left);

        emit leftStatusBarWidget->updateNotification("Canny filter applied!", MainStatusBarLeftWidget::STYLE_VALID);

        if(!stereoWidget->getRighImageWidget()->hasImage())
        {
            return;
        }

        cv::Mat right = stereoWidget->getRighImageWidget()->getImage();

        ip.canny(right, cp->getHThrA(), cp->getHThrB(), cp->getAperture(), cp->getGMagnitude());
        stereoWidget->getRighImageWidget()->setImage(right);
    }
}

/**************************************************************
 **************************************************************
 *
 * Canny real time.
 *
 **************************************************************/
void MainWindow::cannyRealTime()
{
    CannyParameters* cp = static_cast<CannyParameters*>(observers->getObserver(ParameterObservers::Observer::OBS_CANNY));

    if(cp->getRealTime())
    {
        appStates.reverse(ApplicationStates::States::STATE_TRANSITORY);

        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();

        ip.canny(left, cp->getHThrA(), cp->getHThrB(), cp->getAperture(), cp->getGMagnitude());
        stereoWidget->getLeftImageWidget()->setImage(left);

        emit leftStatusBarWidget->updateNotification("Canny filter applied!", MainStatusBarLeftWidget::STYLE_VALID);

        if(!stereoWidget->getRighImageWidget()->hasImage())
        {
            return;
        }

        cv::Mat right = stereoWidget->getRighImageWidget()->getImage();

        ip.canny(right, cp->getHThrA(), cp->getHThrB(), cp->getAperture(), cp->getGMagnitude());
        stereoWidget->getRighImageWidget()->setImage(right);
    }
}

/**************************************************************
 **************************************************************
 *
 * Disparity map.
 *
 **************************************************************/
void MainWindow::disparity()
{
    DisparityMapParameters* dmp = static_cast<DisparityMapParameters*>(observers->getObserver(ParameterObservers::OBS_DISPARITY));

    if(!dmp->getRealTime())
    {
        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat lImage = stereoWidget->getLeftImageWidget()->getImage();
        cv::Mat rImage = stereoWidget->getRighImageWidget()->getImage();

        ImageProcessor::StereoMode mode = static_cast<ImageProcessor::StereoMode>(dmp->getAlgorithm());

        try
        {
            std::chrono::high_resolution_clock::time_point ta = std::chrono::high_resolution_clock::now();
            const cv::Mat& disp = ip.disparityMap(lImage, rImage, dmp, mode);
            std::chrono::high_resolution_clock::time_point tb = std::chrono::high_resolution_clock::now();

            emit leftStatusBarWidget->updateNotification(
                                        "OpenCV: Disparity map applied (" +
                                        QString::number(std::chrono::duration_cast<std::chrono::microseconds>(tb - ta).count()) +
                                        " µs)",
                                        MainStatusBarLeftWidget::STYLE_VALID
                                      );

            transformWidget = new StereoTransformWidget(disp, "Disparity map");
            transformWidget->show();
        }
        catch(const cv::Exception& e)
        {
            emit leftStatusBarWidget->updateNotification("OpenCV Error: " + QString::fromStdString(e.err), MainStatusBarLeftWidget::STYLE_INVALID);
            return;
        }
    }
}

/**************************************************************
 **************************************************************
 *
 * Disparity map real time.
 *
 **************************************************************/
void MainWindow::disparityRealTime()
{
    DisparityMapParameters* dmp = static_cast<DisparityMapParameters*>(observers->getObserver(ParameterObservers::OBS_DISPARITY));

    if(dmp->getRealTime())
    {
        ImageProcessor& ip = ImageProcessor::Instance();
        cv::Mat lImage = stereoWidget->getLeftImageWidget()->getImage();
        cv::Mat rImage = stereoWidget->getRighImageWidget()->getImage();

        ImageProcessor::StereoMode mode = static_cast<ImageProcessor::StereoMode>(dmp->getAlgorithm());

        try
        {
            std::chrono::high_resolution_clock::time_point ta = std::chrono::high_resolution_clock::now();
            const cv::Mat& disp = ip.disparityMap(lImage, rImage, dmp, mode);
            std::chrono::high_resolution_clock::time_point tb = std::chrono::high_resolution_clock::now();

            emit leftStatusBarWidget->updateNotification(
                                        "OpenCV: Disparity map applied (" +
                                        QString::number(std::chrono::duration_cast<std::chrono::microseconds>(tb - ta).count()) +
                                        " µs)",
                                        MainStatusBarLeftWidget::STYLE_VALID
                                      );

            transformWidget->setImage(disp);
        }
        catch(const cv::Exception& e)
        {
            emit leftStatusBarWidget->updateNotification("OpenCV Error: " + QString::fromStdString(e.err), MainStatusBarLeftWidget::STYLE_INVALID);
            return;
        }
    }
}

/**************************************************************
 **************************************************************
 *
 * Flann.
 *
 **************************************************************/
void MainWindow::flann()
{
    if (!stereoWidget->getLeftImageWidget()->hasImage() || !stereoWidget->getRighImageWidget()->hasImage())
    {
        return;
    }

    ImageProcessor& ip = ImageProcessor::Instance();

    cv::Mat left = stereoWidget->getLeftImageWidget()->getImage();
    cv::Mat right = stereoWidget->getRighImageWidget()->getImage();
    cv::Mat disp = ip.flann(left, right);

    transformWidget = new StereoTransformWidget(disp, "FLANN");
    transformWidget->show();
}


/**************************************************************
 **************************************************************
 *
 * Sets the dockwidget to nullptr.
 *
 **************************************************************/
void MainWindow::parametersDockWidgetClosed()
{
    parametersDockWidget = nullptr;
}

/**************************************************************
 **************************************************************
 *
 * Dispalays GPU info.
 *
 **************************************************************/
void MainWindow::gpuInfo()
{
    try
    {
        gpuInfoWidget = new CudaGPUInfoWidget();
        gpuInfoWidget->show();
    }
    catch(const CudaRTNotFoundException& e)
    {
        emit leftStatusBarWidget->updateNotification(QString(e.what()), MainStatusBarLeftWidget::STYLE_INVALID);
    }
    catch(const CudaRTResolveException& e)
    {
        emit leftStatusBarWidget->updateNotification(QString(e.what()), MainStatusBarLeftWidget::STYLE_INVALID);
    }
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
 * Generates the dockwidget.
 *
 **************************************************************/
void MainWindow::generateParametersDockWidget()
{
    if(parametersDockWidget != nullptr)
    {
        connect(this, SIGNAL(method(int)), parametersDockWidget, SLOT(generate(int)));
        connect(parametersDockWidget, SIGNAL(destroyed(QObject*)), this, SLOT(parametersDockWidgetClosed()));

        return;
    }

    parametersDockWidget = new ParametersDockWidget(this, observers);
    parametersDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, parametersDockWidget);

    connect(this, SIGNAL(method(int)), parametersDockWidget, SLOT(generate(int)));
    connect(parametersDockWidget, SIGNAL(destroyed(QObject*)), this, SLOT(parametersDockWidgetClosed()));
}
