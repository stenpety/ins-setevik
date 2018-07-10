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

signals:

public slots:

private:
    void createUI();

private slots:
    void showNewCompanyDialog();
    void showEditCompanyDialog();
    void deleteCompany();

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
