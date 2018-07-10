#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>

#include "setevikdb.h"
#include "companiesmgmt.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createUI();
    void createMenu();

public slots:

private slots:
    void showClosePublic();
    void showSetevikDB();
    void showSetevikTimer();

    void showCompaniesMgmt();

public:

private:
    const QString DBPATH = QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                                  QString(), QStandardPaths::LocateDirectory);
    const QString SETEVIKDBFILE = DBPATH + "setevik_db.sqlite";

    QPushButton *closePublicButton;
    QPushButton *setevikDBButton;
    QPushButton *setevikTimerButton;

    QMenu *setevoMenu;
    QAction *closePublicAct;
    QAction *setevikDBAct;
    QAction *setevikTimerAct;

    QMenu *managementMenu;
    QAction *companiesAct;
};

#endif // MAINWINDOW_H
