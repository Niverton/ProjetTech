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
    QLabel*         _imgLabel;
    QLabel*         _imgLabelRight;
    QLabel*         _imgLabelLeft;
    QLabel*         _statusLabel;

    QMenu*          _menuFile;
    QMenu*          _menuAbout;
    QMenu*          _menuEdit;

    QAction*        _openAction;
    QAction*        _quitAction;
    QAction*        _aboutAction;
    QAction*        _cutAction;
    QAction*        _clipAction;

    bool            _imageLoadedIsDraw = false;
    QImage          _imageLoaded;

    bool            _imagesCuttedIsDraw = false;
    QImage          _imageRight;
    QImage          _imageLeft;
    QString         _path;

    QHBoxLayout*    _layout;

    void initMenuBar();
    void mousePressedEvent(QMouseEvent* event, int x_origin, int y_origin);
};

#endif // MAINWINDOW_H
