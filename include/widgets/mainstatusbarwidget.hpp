#ifndef MAINSTATUSBARWIDGET_HPP
#define MAINSTATUSBARWIDGET_HPP

#include <QStatusBar>

class QLabel;

class MainStatusBarLeftWidget : public QWidget
{
    Q_OBJECT

public:
    enum NotificationStyle
    {
        STYLE_VALID = 0,
        STYLE_INVALID
    };

public:
    MainStatusBarLeftWidget(const QString& status = QString(), QWidget* parent = nullptr);
    ~MainStatusBarLeftWidget();

    QString getText() const;

    void setStyleValid();
    void setStyleInvalid();

signals:
    void updateNotification(const QString& notification, NotificationStyle style);

private slots:
    void setNotification(const QString& notification, NotificationStyle style);

private:
    QLabel* statusLabel;

private:
    bool        valid;

    QString     styleValid;
    QString     styleInvalid;
};

class MainStatusBarRightWidget : public QWidget
{
    Q_OBJECT

public:
    MainStatusBarRightWidget(QWidget* parent = nullptr);
    ~MainStatusBarRightWidget();

private slots:
    void updateStereoLeftCoordinates(const QPoint& coord);
    void updateStereoRightCoordinates(const QPoint& coord);

private:
    QLabel* leftLabel;
    QLabel* rightLabel;

    QLabel* xaLabel;
    QLabel* xbLabel;
    QLabel* yaLabel;
    QLabel* ybLabel;
    QLabel* xaValue;
    QLabel* xbValue;
    QLabel* yaValue;
    QLabel* ybValue;
};

#endif // MAINSTATUSBAR_HPP
