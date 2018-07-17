#ifndef SETEVIKDB_H
#define SETEVIKDB_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <iostream>

#include "newsetevikdialog.h"
#include "newcompanydialog.h"

class SetevikDB : public QWidget
{
    Q_OBJECT
public:
    explicit SetevikDB(QWidget *parent = nullptr);

private:
    void createUI();
    void setupDbModels();
    void setupUItoDB();

    void updateCompanyList();

    void updateDetails(const QModelIndex &index);
    const QString getCompanyName(const int companyCode);

signals:

public slots:

private slots:
    void showNewSetevikDialog();
    void showEditSetevikDialog();
    void deleteSetevik();

    void filterSetevik(const QString &filterStr);
    void showNewCompanyDialog();
    void enableButtons(const bool enbld);
    void setSelectionInTableModel(const int index);

    void copySetevikVK();

    void dismissWindow();

public:

private:
    // 0-0
    QPushButton *newButton;
    QPushButton *editButton;
    QPushButton *deleteButton;

    // 1-0
    QTableView *setevikTable;
    QSqlRelationalTableModel *setevikModel;

    // 0-1
    QComboBox *companyComboBox;
    QStringListModel *companyStringModel;
    QSqlRelationalTableModel *companyModel;
    QPushButton *newCompanyButton;

    // 1-1
    QLineEdit *nameLineEdit;
    QLineEdit *companyLineEdit;
    QLineEdit *vkLineEdit;
    QPushButton *copySetevikVKButton;
    QClipboard *clipboard;
    QTextEdit *storyTextEdit;

    // 2-1
    QPushButton *dismissButton;

    // Mapper, Delegate
    QDataWidgetMapper *mapper;
    QSqlRelationalDelegate *delegate;

};

#endif // SETEVIKDB_H
