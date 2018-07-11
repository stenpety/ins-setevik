#ifndef SETEVIKDB_H
#define SETEVIKDB_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class SetevikDB : public QWidget
{
    Q_OBJECT
public:
    explicit SetevikDB(QWidget *parent = nullptr);

private:
    void createUI();
    void setupDb();
    void setupTable();

signals:

public slots:

private slots:
    void showNewSetevikDialog();
    void showEditSetevikDialog();
    void deleteSetevik();

    void copySetevikVK();

public:

private:
    // 0-0
    QPushButton *newButton;
    QPushButton *editButton;
    QPushButton *deleteButton;

    // 1-0
    QTableView *setevikTable;

    // 0-1
    QComboBox *companyComboBox;

    // 1-1
    QLineEdit *nameLineEdit;
    QLineEdit *companyLineEdit;
    QLineEdit *vkLineEdit;
    QPushButton *copySetevikVKButton;
    QLineEdit *storyLineEdit;

    // Model-mapper-delegate
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    QSqlRelationalDelegate *delegate;

};

#endif // SETEVIKDB_H
