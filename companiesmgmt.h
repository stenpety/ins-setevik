#ifndef COMPANIESMGMT_H
#define COMPANIESMGMT_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

#include <iostream>

#include "newcompanydialog.h"

class CompaniesMgmt : public QWidget {

    Q_OBJECT

public:
    explicit CompaniesMgmt(QWidget *parent = nullptr);

private:
    void createUI();
    void setupDb();
    void setupTable();

    void setSelectionInTableModel(const int index);
    void enableButtons(const bool enbld);

signals:

public slots:

private slots:
    void showNewCompanyDialog();
    void showEditCompanyDialog();
    void deleteCompany();

public:

private:
    QPushButton *newButton;
    QPushButton *editButton;
    QPushButton *deleteButton;

    QTableView *companyTable;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    QSqlRelationalDelegate *delegate;
};

#endif // COMPANIESMGMT_H
