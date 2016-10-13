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
    void clipImgSlot();

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
    QAction*        clipAction_;

    bool            imageLoadedIsDraw_ = false;
    QImage         imageLoaded_;

    bool            imagesCuttedIsDraw_ = false;
    QImage          imageRight_;
    QImage          imageLeft_;
    QString         path_;

    QHBoxLayout*    layout_;

    void initMenuBar();
    void mousePressedEvent(QMouseEvent* event, int x_origin, int y_origin);
};

#endif // MAINWINDOW_H
