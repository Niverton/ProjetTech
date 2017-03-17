/*!
 * \file main.cpp
 * \brief Source file containing the main entry point of the program.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.1
 */

#include "mainwindow.hpp"

#include <QApplication>

/**************************************************************
 **************************************************************
 *
 * Main entry point.
 *
 **************************************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
