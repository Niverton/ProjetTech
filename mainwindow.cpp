#include "mainwindow.h"
#include <stdlib.h>

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
}

MainWindow::~MainWindow() {
  deleteMenus();
  deleteActions();
}

void MainWindow::createMenus(){
  this->menu_about = new QMenu("A propos");
  this->menu_file = new QMenu("Fichier");

  this->menuBar()->addMenu(this->menu_file);
  this->menuBar()->addMenu(this->menu_about);
}

void MainWindow::deleteMenus(){
  delete(this->menu_about);
  delete(this->menu_file);
}

void MainWindow::createActions(){
  this->action_about = new QAction("A propos",this);
  this->action_open_file = new QAction("Ouvrir", this);
  this->action_quit = new QAction("Quitter", this);

  this->menu_about->addAction(this->action_about);
  this->menu_file->addAction(this->action_open_file);
  this->menu_file->addAction(this->action_quit);
}

void MainWindow::deleteActions(){
  delete(this->action_about);
  delete(this->action_open_file);
}

void MainWindow::about(){
  QMessageBox* about_msgBox = new QMessageBox();
  about_msgBox->setText("BLA BLA BLA");
  about_msgBox->show();
}

void MainWindow::openFile(){
  QFileDialog* f_dialog = new QFileDialog();
  f_dialog->show();
  QString file_name = f_dialog->getOpenFileName();
}

void MainWindow::quit(){
  exit(EXIT_SUCCESS);
}
