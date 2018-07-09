#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>

#include "setevikdb.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private:
    void createUI();
    void createMenu();

private slots:
    void showClosePublic();
    void showSetevikDB();

private:
    const QString DBPATH = QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                                  QString(), QStandardPaths::LocateDirectory);
    const QString SETEVIKDBFILE = DBPATH + "setevik_db.sqlite";

    QPushButton *closePublicButton;
    QPushButton *setevikDBButton;

    QMenu *setevoMenu;
    QAction *closePublicAct;
    QAction *setevikDBAct;
};

#endif // MAINWINDOW_H
