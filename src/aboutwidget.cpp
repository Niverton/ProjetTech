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

#include "aboutwidget.hpp"

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

    QVBoxLayout* vBox = new QVBoxLayout(this);

    textLabel = new QLabel(this);
    textLabel->setText(text);

    QPixmap pMap = QPixmap(":/logo/qt-logo.png");
    qtImageLabel = new QLabel(this);
    qtImageLabel->setPixmap(pMap);

    pMap = QPixmap(":/logo/ocv-logo.png");
    ocvImageLabel = new QLabel(this);
    ocvImageLabel->setPixmap(pMap);

    closePushButton = new QPushButton("Close", this);

    vBox->addWidget(textLabel, 0, Qt::AlignCenter);
    vBox->addWidget(qtImageLabel, 0, Qt::AlignHCenter);
    vBox->addWidget(ocvImageLabel, 0, Qt::AlignCenter);
    vBox->addWidget(closePushButton, 0, Qt::AlignRight);

    connect(closePushButton, SIGNAL(clicked(bool)), this, SLOT(exit()));

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2),
         (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
AboutWidget::~AboutWidget() {}

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
