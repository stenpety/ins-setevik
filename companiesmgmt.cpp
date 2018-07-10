#include "companiesmgmt.h"

CompaniesMgmt::CompaniesMgmt(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MLM Companies");
    createUI();

    setupDb();
    setupTable();
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
    connect(editButton, &QPushButton::clicked, this, &CompaniesMgmt::showEditCompanyDialog);
    layoutButtons->addWidget(editButton);

    deleteButton = new QPushButton(tr("&Delete"));
    connect(deleteButton, &QPushButton::clicked, this, &CompaniesMgmt::deleteCompany);
    layoutButtons->addWidget(deleteButton);

    companyTable = new QTableView();
    layoutMain->addWidget(companyTable);

}

void CompaniesMgmt::setupDb() {

    model = new QSqlRelationalTableModel(companyTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("company");

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Company"));
    model->setHeaderData(model->fieldIndex("vk"), Qt::Horizontal, tr("VK Group"));
    model->setHeaderData(model->fieldIndex("keyWord"), Qt::Horizontal, tr("Key words"));

    if (!model->select()) {
        // TODO: show error
        return;
    }
}

void CompaniesMgmt::setupTable() {

    companyTable->setModel(model);
    delegate = new QSqlRelationalDelegate(companyTable);
    companyTable->setItemDelegate(delegate);
    companyTable->setColumnHidden(model->fieldIndex("id"), true);
    companyTable->setSelectionMode(QAbstractItemView::SingleSelection);
    companyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    companyTable->resizeColumnsToContents();

    mapper = new QDataWidgetMapper();
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(model);
    mapper->setItemDelegate(delegate);
    connect(companyTable->selectionModel(), &QItemSelectionModel::currentRowChanged,
            mapper, &QDataWidgetMapper::setCurrentModelIndex);
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

        // TODO: adjust columns width after insertion of a new item
    }
}

void CompaniesMgmt::showEditCompanyDialog() {

    int rowToEdit = mapper->currentIndex();

    auto *editCompanyDialog = new NewCompanyDialog(this);
    editCompanyDialog->nameLineEdit->setText(model->record(rowToEdit).value("name").toString());
    editCompanyDialog->vkLineEdit->setText(model->record(rowToEdit).value("vk").toString());
    editCompanyDialog->keyWordLineEdit->setText(model->record(rowToEdit).value("keyWord").toString());

    if (editCompanyDialog->exec()) {

        model->setData(model->index(rowToEdit, 1), editCompanyDialog->nameLineEdit->text());
        model->setData(model->index(rowToEdit, 2), editCompanyDialog->vkLineEdit->text());
        model->setData(model->index(rowToEdit, 3), editCompanyDialog->keyWordLineEdit->text());
        model->submitAll();

        // TODO: adjust columns width after insertion of a new item
    }
}

void CompaniesMgmt::deleteCompany() {

    QMessageBox::StandardButton deleteDialog;
    deleteDialog = QMessageBox::question(this, "Delete a company", "Are you sure?",
                                         QMessageBox::Yes|QMessageBox::No);
    if (deleteDialog == QMessageBox::Yes) {
        int rowToDelete = mapper->currentIndex();

        if (!(model->removeRow(rowToDelete))) {
            // TODO: show error
            return;
        }
        model->submitAll();
        mapper->submit();

        mapper->setCurrentIndex(qMax(1, rowToDelete-1));
        companyTable->selectRow(qMax(1, rowToDelete-1));
    }
}
