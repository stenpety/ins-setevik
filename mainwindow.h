#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>


class MainWindow : public QMainWindow
{
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
    QPushButton *closePublicButton;
    QPushButton *setevikDBButton;

    QMenu *setevoMenu;
    QAction *closePublicAct;
    QAction *setevikDBAct;
};

#endif // MAINWINDOW_H
