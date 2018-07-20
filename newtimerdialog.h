#ifndef NEWTIMERDIALOG_H
#define NEWTIMERDIALOG_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class NewTimerDialog : public QDialog {

    Q_OBJECT

public:
    explicit NewTimerDialog(QWidget *parent = nullptr,
                            const QString &title = "Add new");

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

#endif // NEWTIMERDIALOG_H
