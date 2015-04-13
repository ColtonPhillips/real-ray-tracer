// Colton Phillips
// V00680089
// Enjoy the assignment. see any additional readme files for features it contains!
// This is self documenting code for the most part it should be obvious what
// is going on although there are some optimization tricks that could be tricky.

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
