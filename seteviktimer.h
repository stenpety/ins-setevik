#ifndef SETEVIKTIMER_H
#define SETEVIKTIMER_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class SetevikTimer : public QMainWindow {

    Q_OBJECT

public:
    explicit SetevikTimer(QWidget *parent = nullptr);

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

#endif // SETEVIKTIMER_H
