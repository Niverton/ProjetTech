#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
  createMenus();
  createActions();

  //About
  QObject::connect(this->action_about, &QAction::triggered,
                   this, &MainWindow::about);

  //Open File
  QObject::connect(this->action_open_file, &QAction::triggered,
                   this, &MainWindow::openFile);

  //Quit application
  QObject::connect(this->action_quit, &QAction::triggered,
                   this, &MainWindow::quit);

  this->image_label = new QLabel();
}

MainWindow::~MainWindow() {

}

void MainWindow::createMenus(){
  this->menu_about = new QMenu("A propos", this);
  this->menu_file = new QMenu("Fichier", this);

  this->menuBar()->addMenu(this->menu_file);
  this->menuBar()->addMenu(this->menu_about);
}

void MainWindow::createActions(){
  this->action_about = new QAction("A propos",this);
  this->action_open_file = new QAction("Ouvrir", this);
  this->action_quit = new QAction("Quitter", this);

  this->menu_about->addAction(this->action_about);
  this->menu_file->addAction(this->action_open_file);
  this->menu_file->addAction(this->action_quit);
}

void MainWindow::about(){
  QMessageBox* about_msgBox = new QMessageBox();
  about_msgBox->setText("BLA BLA BLA");
  about_msgBox->show();
}

void MainWindow::openFile(){
  QFileDialog* f_dialog = new QFileDialog();
  f_dialog->show();

  //try{
  QString file_name = f_dialog->getOpenFileName();
  this->display_image(file_name);
  /*}catch{
  QMessageBox* msgBox = new QMessageBox();
  msgBox->setText("file corrupt");
  msgBox->show();
  }*/
}

void MainWindow::quit(){
  exit(EXIT_SUCCESS);
}

void MainWindow::display_image(QString path){
  QImageReader* img_reader = new QImageReader(path);

  this->pix_map = QPixmap::fromImage(img_reader->read());
}
