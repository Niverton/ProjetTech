#include "widgets/images/stereoimageswidget.hpp"

#include "widgets/images/imagecropwidget.hpp"
#include "utils/applicationstates.hpp"

#include <QScrollArea>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFile>
#include <QPixmap>

StereoImagesWidget::StereoImagesWidget(QWidget* parent, ApplicationStates* states) : QWidget(parent)
{
    QHBoxLayout* hBox = new QHBoxLayout(this);

    QScrollArea* scA = new QScrollArea(this);
    QScrollArea* scB = new QScrollArea(this);
    scA->setAlignment(Qt::AlignCenter);
    scB->setAlignment(Qt::AlignCenter);

    QFile file(":/styles/stereoimagewidget/stereoimagewidget.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = file.readAll();
    setStyleSheet(styleSheet);
    file.close();

    stereoImageLeft = new ImageCropWidget(this, states, 0);
    stereoImageLeft->setStyleSheet(styleSheet);
    stereoImageRight = new ImageCropWidget(this, states, 1);
    stereoImageRight->setStyleSheet(styleSheet);

    QPixmap initA = QPixmap(":/images/stereoimagewidget/stereo1.svg");
    stereoImageLeft->setPixmap(initA);

    QPixmap initB = QPixmap(":/images/stereoimagewidget/stereo2.svg");
    stereoImageRight->setPixmap(initB);

    scA->setWidget(stereoImageLeft);
    scB->setWidget(stereoImageRight);

    hBox->setAlignment(stereoImageLeft, Qt::AlignVCenter);
    hBox->setAlignment(stereoImageRight, Qt::AlignVCenter);

    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(scA);
    splitter->addWidget(scB);

    hBox->addWidget(splitter);

    setLayout(hBox);
}

StereoImagesWidget::~StereoImagesWidget() {}

ImageCropWidget* StereoImagesWidget::getLeftImageWidget() const
{
    return stereoImageLeft;
}

ImageCropWidget* StereoImagesWidget::getRighImageWidget() const
{
    return stereoImageRight;
}

