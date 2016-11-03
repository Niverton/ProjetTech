#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QImage>
#include <QHBoxLayout>
#include <QSize>

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
    QSize sizeHint() const;

private slots:
    void renderMessageBox();
    void openFile();
    void cutImgSlot();
    void clipImgSlot();
    void blurSlot();
    void sobelSlot();
    void cannySlot();

private:
    QLabel*         _imgLabel;
    QLabel*         _imgLabelRight;
    QLabel*         _imgLabelLeft;
    QLabel*         _statusLabel;

    QMenu*          _menuFile;
    QMenu*          _menuAbout;
    QMenu*          _menuEdit;
    QMenu*          _menuOpenCV;

    //MenuFile
    QAction*        _openAction;
    QAction*        _quitAction;

    //About
    QAction*        _aboutAction;

    //Edit
    QAction*        _cutAction;
    QAction*        _clipAction;

    //OpenCV
    QAction*        _blurAction;
    QAction*        _sobelAction;
    QAction*        _cannyAction;

    bool            _imageLoadedIsDraw = false;
    QImage          _imageLoaded;

    bool            _imagesCuttedIsDraw = false;
    QImage          _imageRight;
    QImage          _imageLeft;
    QString         _path;

    QHBoxLayout*    _layout;

    void initMenuBar();
};

#endif // MAINWINDOW_H
