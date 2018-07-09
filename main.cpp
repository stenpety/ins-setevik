#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication setevikApp(argc, argv);

    MainWindow mainWin;
    mainWin.show();

    return setevikApp.exec();
}
