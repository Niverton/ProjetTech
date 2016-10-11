#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QImage>
#include <QHBoxLayout>

class QMenu;
class QAction;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);
    void resizeLoadedImage();

private slots:
    void renderMessageBox();
    void openFile();
    void cutImgSlot();

private:
    QLabel*         imgLabel_;
    QLabel*         imgLabelRight_;
    QLabel*         imgLabelLeft_;
    QLabel*         statusLabel_;

    QMenu*          menuFile_;
    QMenu*          menuAbout_;
    QMenu*          menuEdit_;

    QAction*        openAction_;
    QAction*        quitAction_;
    QAction*        aboutAction_;
    QAction*        cutAction_;

    bool            imageLoadedIsDraw_ = false;
    QImage*         imageLoaded_;

    bool            imagesCuttedIsDraw_ = false;
    QImage          imageRight_;
    QImage          imageLeft_;
    QString         path_;

    QHBoxLayout*    layout_;

    void initMenuBar();
    void cutImage(QImage* img);
    void drawImage(QImage img);
    void drawImages(QImage imgLeft, QImage imgRight);
};

#endif // MAINWINDOW_H
