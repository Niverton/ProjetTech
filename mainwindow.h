#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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

private slots:
    void renderMessageBox();
    void openFile();

private:
    QLabel*     imgLabel_;
    QLabel*     statusLabel_;

    QMenu*      menuFile_;
    QMenu*      menuAbout_;

    QAction*    openAction_;
    QAction*    quitAction_;
    QAction*    aboutAction_;

    QString     path_;
};

#endif // MAINWINDOW_H
