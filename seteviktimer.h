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
    void showNewTimerDialog();
    void showEditTimerDialog();
    void deleteTimer();

    void dismissWindow();

public:

private:
    // 0-0
    QPushButton *newButton;
    QPushButton *editButton;
    QPushButton *deleteButton;

    // 1-0
    QTableView *timerTable;
    QSqlRelationalTableModel *timerModel;

    // 2-0
    QPushButton *dismissButton;

};

#endif // SETEVIKTIMER_H
