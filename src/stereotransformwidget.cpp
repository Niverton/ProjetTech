/*!
 * \file stereotransformwidget.cpp
 * \brief Implementation of the methods of the StereoTransformWidget class declared in the stereotransformwidget.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2017-02-02
 * \version 0.1
 */

#include "stereotransformwidget.hpp"

#include "imagewidget.hpp"
#include "imageprocessor.hpp"

#include <QMenuBar>
#include <QVBoxLayout>
#include <QFileDialog>

/**************************************************************
 **************************************************************
 *
 * Constructor
 *
 **************************************************************/
StereoTransformWidget::StereoTransformWidget(const cv::Mat& image, const QString& title) : QWidget(nullptr)
{
    setWindowTitle(title);
    setMinimumSize(400, 300);

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* menuAction = new QMenu("Actions", menuBar);

    QAction* actionSave = new QAction("Save", menuAction);
    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));

    QAction* actionClose = new QAction("Close", menuAction);
    actionClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    menuBar->addMenu(menuAction);
    menuAction->addAction(actionSave);
    menuAction->addAction(actionClose);

    QVBoxLayout* vBox = new QVBoxLayout(this);
    imageWidget = new ImageWidget(this);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageWidget->setImage(image);

    vBox->addWidget(menuBar);
    vBox->addWidget(imageWidget);
    vBox->setAlignment(imageWidget, Qt::AlignHCenter);

    connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(exit()));
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
StereoTransformWidget::~StereoTransformWidget() {}

/**************************************************************
 **************************************************************
 *
 * Close event.
 *
 **************************************************************/
void StereoTransformWidget::closeEvent(QCloseEvent* event)
{
    QWidget::closeEvent(event);
    deleteLater();
}

/**************************************************************
 **************************************************************
 *
 * Save.
 *
 **************************************************************/
void StereoTransformWidget::save()
{
    QString fName = QFileDialog::getSaveFileName(this, "Save image", QString(), "Images (*.png *.jpg)");

    if(!fName.isEmpty())
    {
        cv::Mat imCV = imageWidget->getImage();
        ImageProcessor& ip = ImageProcessor::Instance();
        QImage imQT = ip.cvMatToImage(imCV);

        QString sub = fName.mid(fName.count() - 3, 3);
        sub = sub.toLower();

        if(sub == "png")
        {
            imQT.save(fName, "PNG");
        }
        else if(sub == "jpg")
        {
            imQT.save(fName, "JPG");
        }
        else
        {
            imQT.save(fName, "PNG");
        }
    }
}

/**************************************************************
 **************************************************************
 *
 * Close.
 *
 **************************************************************/
void StereoTransformWidget::exit()
{
    close();
}
