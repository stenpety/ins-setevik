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
    void setupModel();
    void setupUItoDB();

signals:

public slots:



private slots:
    void showNewSetevikDialog();

    void activateSubmitButton();

public:

private:
    QTableView *setevikTable;
    QSqlRelationalTableModel *setevikModel;
    QPushButton *newSetevikButton;

    QLineEdit *startDateLineEdit;
    QLineEdit *durationLineEdit;
    QTextEdit *descriptionTextEdit;
    QTextEdit *penaltyTextEdit;

    QPushButton *submitButton;
    QPushButton *cancelButton;

    // Mapper, Delegate
    QDataWidgetMapper *mapper;
    QSqlRelationalDelegate *delegate;
};

#endif // NEWTIMERDIALOG_H
