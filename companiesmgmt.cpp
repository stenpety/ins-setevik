#include "companiesmgmt.h"

CompaniesMgmt::CompaniesMgmt(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MLM Companies");
    createUI();

    // db model
    model = new QSqlRelationalTableModel(companyTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("company");

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Company"));
    model->setHeaderData(model->fieldIndex("vk"), Qt::Horizontal, tr("VK Group"));
    model->setHeaderData(model->fieldIndex("keyWord"), Qt::Horizontal, tr("Key words"));

    if (!model->select()) {
        //show error
        return;
    }

    companyTable->setModel(model);
    companyTable->setItemDelegate(new QSqlRelationalDelegate(companyTable));
    companyTable->setColumnHidden(model->fieldIndex("id"), true);
    companyTable->setSelectionMode(QAbstractItemView::SingleSelection);

}

void CompaniesMgmt::createUI() {
    auto *layoutMain = new QVBoxLayout();
    setLayout(layoutMain);

    auto *layoutButtons = new QHBoxLayout();
    layoutMain->addLayout(layoutButtons);

    newButton = new QPushButton(tr("&New"));
    connect(newButton, &QPushButton::clicked, this, &CompaniesMgmt::showNewCompanyDialog);
    layoutButtons->addWidget(newButton);

    editButton = new QPushButton(tr("&Edit"));
    layoutButtons->addWidget(editButton);

    deleteButton = new QPushButton(tr("&Delete"));
    layoutButtons->addWidget(deleteButton);

    companyTable = new QTableView();
    layoutMain->addWidget(companyTable);

}

void CompaniesMgmt::showNewCompanyDialog() {
    auto *newCompanyDialog = new NewCompanyDialog(this);
    if (newCompanyDialog->exec()) {

        int rowCount = model->rowCount();
        model->insertRows(rowCount, 1);
        model->setData(model->index(rowCount, 1), newCompanyDialog->nameLineEdit->text());
        model->setData(model->index(rowCount, 2), newCompanyDialog->vkLineEdit->text());
        model->setData(model->index(rowCount, 3), newCompanyDialog->keyWordLineEdit->text());
        model->submitAll();
    }
}
