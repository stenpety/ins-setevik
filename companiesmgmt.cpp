#include "companiesmgmt.h"

CompaniesMgmt::CompaniesMgmt(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MLM Companies");
    createUI();

    setupDb();
    setupTable();

    enableButtons(model->rowCount() > 0);
}

void CompaniesMgmt::createUI() {

    setMinimumSize(640, 480);

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

    dismissButton = new QPushButton(tr("&Dismiss"));
    connect(dismissButton, &QPushButton::clicked, this, &CompaniesMgmt::dismissWindow);
    layoutMain->addWidget(dismissButton);
}

void CompaniesMgmt::setupDb() {

    model = new QSqlRelationalTableModel(companyTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("companies");

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Company"));
    model->setHeaderData(model->fieldIndex("vk"), Qt::Horizontal, tr("VK Group"));
    model->setHeaderData(model->fieldIndex("keyWord"), Qt::Horizontal, tr("Key words"));

    if (!model->select()) {
        QMessageBox::critical(this, "Unable to setup model",
                              "Error creating table model: " + model->lastError().text());
        return;
    }
    model->sort(1, Qt::AscendingOrder);
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

    setSelectionInTableModel(0);
}

void CompaniesMgmt::setSelectionInTableModel(const int index) {
    mapper->setCurrentIndex(index);
    companyTable->selectRow(index);
}

void CompaniesMgmt::enableButtons(const bool enbld) {
    editButton->setEnabled(enbld);
    deleteButton->setEnabled(enbld);
}

int CompaniesMgmt::rowByValue(const QString &value) {
    int i;
    for (i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("name").toString() == value) {
            return i;
        }
    }
    return -1;
}

void CompaniesMgmt::showNewCompanyDialog() {
    auto *newCompanyDialog = new NewCompanyDialog(this, "Add new MLM Company");
    if (newCompanyDialog->exec()) {

        int rowCount = model->rowCount();
        model->insertRows(rowCount, 1);
        model->setData(model->index(rowCount, 1), newCompanyDialog->nameLineEdit->text());
        model->setData(model->index(rowCount, 2), newCompanyDialog->vkLineEdit->text());
        model->setData(model->index(rowCount, 3), newCompanyDialog->keyWordLineEdit->text());
        model->submitAll();

        int rowToSelect = rowByValue(newCompanyDialog->nameLineEdit->text());
        setSelectionInTableModel(rowToSelect);
        enableButtons(model->rowCount() > 0);

        // TODO: adjust columns width after insertion of a new item
    }
}

void CompaniesMgmt::showEditCompanyDialog() {

    int rowToEdit = mapper->currentIndex();

    auto *editCompanyDialog = new NewCompanyDialog(this, "Edit MLM Company");
    editCompanyDialog->nameLineEdit->setText(model->record(rowToEdit).value("name").toString());
    editCompanyDialog->vkLineEdit->setText(model->record(rowToEdit).value("vk").toString());
    editCompanyDialog->keyWordLineEdit->setText(model->record(rowToEdit).value("keyWord").toString());

    if (editCompanyDialog->exec()) {

        model->setData(model->index(rowToEdit, 1), editCompanyDialog->nameLineEdit->text());
        model->setData(model->index(rowToEdit, 2), editCompanyDialog->vkLineEdit->text());
        model->setData(model->index(rowToEdit, 3), editCompanyDialog->keyWordLineEdit->text());
        model->submitAll();

        int rowToSelect = rowByValue(editCompanyDialog->nameLineEdit->text());
        setSelectionInTableModel(rowToSelect);

        // TODO: adjust columns width after editing an item
    }
}

void CompaniesMgmt::deleteCompany() {

    int rowToDelete = mapper->currentIndex();
    QMessageBox::StandardButton deleteDialog;
    QString companyToDelete = model->record(rowToDelete).value(1).toString();
    deleteDialog = QMessageBox::question(this, "Delete a company", "Delete " + companyToDelete + "?\nAre you sure?",
                                         QMessageBox::Yes|QMessageBox::No);
    if (deleteDialog == QMessageBox::Yes) {


        if (!(model->removeRow(rowToDelete))) {
            QMessageBox::critical(this, "Unable to delete item",
                                  "Error deleting item: " + model->lastError().text());
            return;
        }
        model->submitAll();
        mapper->submit();

        if (model->rowCount() > 0) {
            setSelectionInTableModel(rowToDelete);
        } else {
            setSelectionInTableModel(-1);
            enableButtons(false);
        }
    }
}

void CompaniesMgmt::dismissWindow() {
    this->hide();
}
