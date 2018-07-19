#ifndef CLOSEPUBLIC_H
#define CLOSEPUBLIC_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class ClosePublic : public QWidget {

    Q_OBJECT

public:
    explicit ClosePublic(QWidget *parent = nullptr);

private:
    void createUI();

signals:

public slots:

private slots:
    void dismissWindow();

public:

private:
    QPushButton *dismissButton;

};

#endif // CLOSEPUBLIC_H
