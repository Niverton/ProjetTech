/*!
 * \file aboutwidget.cpp
 * \brief Implementation of the methods of the AboutWidget class declared in the aboutwidget.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#include "widgets/aboutwidget.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
AboutWidget::AboutWidget(const QString& text) : QWidget(nullptr), text(text)
{
    setWindowTitle("About");
    setMinimumSize(300, 400);
    setWindowFlags(Qt::WindowCloseButtonHint);

    QVBoxLayout* vBox = new QVBoxLayout();

    textLabel = new QLabel(this);
    textLabel->setText(text);

    QPixmap pMap = QPixmap(":/logos/qt/qt-logo.png");
    qtImageLabel = new QLabel(this);
    qtImageLabel->setPixmap(pMap);
    qtImageLabel->setContentsMargins(0, 2, 0, 0);

    pMap = QPixmap(":/logos/ocv/ocv-logo.png");
    ocvImageLabel = new QLabel(this);
    ocvImageLabel->setPixmap(pMap);
    ocvImageLabel->setContentsMargins(0, 2, 0, 0);

    pMap = QPixmap(":/logos/cuda/cuda-logo.png");
    cudaImageLabel = new QLabel(this);
    cudaImageLabel->setPixmap(pMap);
    cudaImageLabel->setContentsMargins(0, 2, 0, 0);

    closePushButton = new QPushButton("Close", this);

    QLabel* qtHyperLinkLabel = new QLabel("<a href='https://www.qt.io/'>https://www.qt.io/</a>", this);
    qtHyperLinkLabel->setContentsMargins(0, 0, 0, 2);
    qtHyperLinkLabel->setTextFormat(Qt::RichText);
    qtHyperLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    qtHyperLinkLabel->setOpenExternalLinks(true);

    QLabel* ocvHyperLinkLabel = new QLabel("<a href='http://opencv.org/'>http://opencv.org/</a>", this);
    ocvHyperLinkLabel->setContentsMargins(0, 0, 0, 2);
    ocvHyperLinkLabel->setTextFormat(Qt::RichText);
    ocvHyperLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ocvHyperLinkLabel->setOpenExternalLinks(true);

    QLabel* nvidiaHyperLinkLabel = new QLabel("<a href='http://www.nvidia.com'>http://www.nvidia.com</a>", this);
    nvidiaHyperLinkLabel->setContentsMargins(0, 0, 0, 0);
    nvidiaHyperLinkLabel->setTextFormat(Qt::RichText);
    nvidiaHyperLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    nvidiaHyperLinkLabel->setOpenExternalLinks(true);

    QLabel* cudaHyperLinkLabel = new QLabel("<a href='http://www.nvidia.com/object/cuda_home_new.html'>http://www.nvidia.com/object/cuda_home_new.html</a>", this);
    cudaHyperLinkLabel->setContentsMargins(0, 0, 0, 2);
    cudaHyperLinkLabel->setTextFormat(Qt::RichText);
    cudaHyperLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    cudaHyperLinkLabel->setOpenExternalLinks(true);

    vBox->addWidget(textLabel, 0, Qt::AlignCenter);
    vBox->addWidget(qtImageLabel, 0, Qt::AlignCenter);
    vBox->addWidget(qtHyperLinkLabel, 0, Qt::AlignCenter);
    vBox->addWidget(ocvImageLabel, 0, Qt::AlignCenter);
    vBox->addWidget(ocvHyperLinkLabel, 0, Qt::AlignCenter);
    vBox->addWidget(cudaImageLabel, 0, Qt::AlignCenter);
    vBox->addWidget(nvidiaHyperLinkLabel, 0, Qt::AlignCenter);
    vBox->addWidget(cudaHyperLinkLabel, 0, Qt::AlignCenter);
    vBox->addWidget(closePushButton, 0, Qt::AlignRight);


    connect(closePushButton, SIGNAL(clicked(bool)), this, SLOT(exit()));

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2),
         (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));

    setLayout(vBox);
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
AboutWidget::~AboutWidget() {}

/**************************************************************
 **************************************************************
 *
 * Close event..
 *
 **************************************************************/
void AboutWidget::closeEvent(QCloseEvent* event)
{
    QWidget::closeEvent(event);
    deleteLater();
}

/**************************************************************
 **************************************************************
 *
 * Close.
 *
 **************************************************************/
void AboutWidget::exit()
{
    close();
}
