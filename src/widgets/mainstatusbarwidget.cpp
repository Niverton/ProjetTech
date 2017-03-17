#include "widgets/mainstatusbarwidget.hpp"

#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

/**************************************************************
 **************************************************************
 *
 * Left constructor.
 *
 **************************************************************/
MainStatusBarLeftWidget::MainStatusBarLeftWidget(const QString& status, QWidget* parent) : QWidget(parent), valid(true)
{
    setMinimumWidth(INT16_MAX);

    QFile file(":/styles/mainstatusbarwidget/notificationvalid.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = file.readAll();
    setStyleSheet(styleSheet);
    file.close();

    styleValid = styleSheet;

    file.setFileName(":/styles/mainstatusbarwidget/notificationinvalid.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    styleSheet = file.readAll();
    file.close();

    styleInvalid = styleSheet;

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->setContentsMargins(0, 0, 0, 0);

    statusLabel = new QLabel(status);
    statusLabel->setWordWrap(true);

    hBox->addWidget(statusLabel);

    setLayout(hBox);

    connect(this, SIGNAL(updateNotification(const QString&, NotificationStyle)), this, SLOT(setNotification(const QString&, NotificationStyle)));
}

/**************************************************************
 **************************************************************
 *
 * Left destructor.
 *
 **************************************************************/
MainStatusBarLeftWidget::~MainStatusBarLeftWidget() {}

/**************************************************************
 **************************************************************
 *
 * Get status text;
 *
 **************************************************************/
QString MainStatusBarLeftWidget::getText() const
{
    return statusLabel->text();
}

/**************************************************************
 **************************************************************
 *
 * Set text;
 *
 **************************************************************/
void MainStatusBarLeftWidget::setNotification(const QString& notification, NotificationStyle style)
{
    switch(style)
    {
        case NotificationStyle::STYLE_VALID:
        {
            if(!valid)
            {
                setStyleSheet(styleValid);
                valid = true;
            }

            break;
        }

        case NotificationStyle::STYLE_INVALID:
        {
            if(valid)
            {
                setStyleSheet(styleInvalid);
                valid = false;
            }

            break;
        }
    }

    statusLabel->setText(notification);
}

/**************************************************************
 **************************************************************
 *
 * Right constructor.
 *
 **************************************************************/
MainStatusBarRightWidget::MainStatusBarRightWidget(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->setContentsMargins(0, 0, 0, 0);

    leftLabel = new QLabel("Left");
    leftLabel->setObjectName("LeftLabel");

    rightLabel = new QLabel("Right");
    rightLabel->setContentsMargins(0, 0, 0, 0);
    rightLabel->setObjectName("RightLabel");

    xaLabel = new QLabel("x:");
    xbLabel = new QLabel("x:");
    yaLabel = new QLabel("y:");
    ybLabel = new QLabel("y:");

    xaValue = new QLabel("0");
    xbValue = new QLabel("0");
    yaValue = new QLabel("0");
    ybValue = new QLabel("0");

    QWidget* sepA = new QWidget();
    sepA->setMinimumWidth(1);
    sepA->setMaximumWidth(1);
    sepA->setObjectName("SeparatorA");

    hBox->addWidget(sepA);
    hBox->addWidget(leftLabel);
    hBox->addWidget(xaLabel);
    hBox->addWidget(xaValue);
    hBox->addWidget(yaLabel);
    hBox->addWidget(yaValue);

    QWidget* sepB = new QWidget();
    sepB->setMinimumWidth(1);
    sepB->setMaximumWidth(1);
    sepB->setObjectName("SeparatorB");

    hBox->addWidget(sepB);
    hBox->addWidget(rightLabel);
    hBox->addWidget(xbLabel);
    hBox->addWidget(xbValue);
    hBox->addWidget(ybLabel);
    hBox->addWidget(ybValue);

    setLayout(hBox);
}

/**************************************************************
 **************************************************************
 *
 * Right destructor.
 *
 **************************************************************/
MainStatusBarRightWidget::~MainStatusBarRightWidget() {}

/**************************************************************
 **************************************************************
 *
 * Left coordinates.
 *
 **************************************************************/
void MainStatusBarRightWidget::updateStereoLeftCoordinates(const QPoint& coord)
{
    xaValue->setText(QString::number(coord.x()));
    yaValue->setText(QString::number(coord.y()));
}

/**************************************************************
 **************************************************************
 *
 * Left coordinates.
 *
 **************************************************************/
void MainStatusBarRightWidget::updateStereoRightCoordinates(const QPoint& coord)
{
    xbValue->setText(QString::number(coord.x()));
    ybValue->setText(QString::number(coord.y()));
}

