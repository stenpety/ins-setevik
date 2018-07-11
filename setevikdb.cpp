#include "setevikdb.h"

SetevikDB::SetevikDB(QWidget *parent) : QWidget(parent) {

    setWindowTitle("Setevo Personalities");
    createUI();

    setupDbModels();
    setupUItoDB();

}

void SetevikDB::createUI() {

    setMinimumSize(640, 480);

    auto *layoutMain = new QGridLayout;

    // Buttons: 0-0
    auto *layoutButtons = new QHBoxLayout();

    newButton = new QPushButton(tr("&New"));
    connect(newButton, &QPushButton::clicked, this, &SetevikDB::showNewSetevikDialog);
    layoutButtons->addWidget(newButton);

    editButton = new QPushButton(tr("&Edit"));
    connect(editButton, &QPushButton::clicked, this, &SetevikDB::showEditSetevikDialog);
    layoutButtons->addWidget(editButton);

    deleteButton = new QPushButton(tr("&Delete"));
    connect(deleteButton, &QPushButton::clicked, this, &SetevikDB::deleteSetevik);
    layoutButtons->addWidget(deleteButton);

    layoutMain->addLayout(layoutButtons, 0,0 );

    // Table: 1-0
    setevikTable = new QTableView();
    layoutMain->addWidget(setevikTable, 1, 0);

    // Company combo-box: 0-1
    companyComboBox = new QComboBox();
    layoutMain->addWidget(companyComboBox, 0, 1);

    // Setevik details: 1-1
    auto layoutDetails = new QGridLayout();

    auto nameLabel = new QLabel(tr("Name"));
    layoutDetails->addWidget(nameLabel, 0, 0);
    nameLineEdit = new QLineEdit();
    layoutDetails->addWidget(nameLineEdit, 0, 1);

    auto companyLabel = new QLabel(tr("Company"));
    layoutDetails->addWidget(companyLabel, 1, 0);
    companyLineEdit = new QLineEdit();
    layoutDetails->addWidget(companyLineEdit, 1, 1);

    auto vkLabel = new QLabel(tr("VK profile"));
    layoutDetails->addWidget(vkLabel, 2, 0);
    vkLineEdit = new QLineEdit();
    layoutDetails->addWidget(vkLineEdit, 2, 1);
    copySetevikVKButton = new QPushButton(tr("Copy"));
    connect(copySetevikVKButton, &QPushButton::clicked, this, &SetevikDB::copySetevikVK);
    layoutDetails->addWidget(copySetevikVKButton, 2, 2);

    auto storyLabel = new QLabel(tr("Story"));
    layoutDetails->addWidget(storyLabel, 3, 0);
    storyTextEdit = new QTextEdit();
    layoutDetails->addWidget(storyTextEdit, 3, 1);

    layoutMain->addLayout(layoutDetails, 1, 1);

    setLayout(layoutMain);
}

void SetevikDB::setupDbModels() {

    // Companies
    QStringList companies;
    QSqlQuery query;
    query.prepare("SELECT name FROM company");
    if (!query.exec()) {
        qWarning() << "Companies query ERROR: " << query.lastError().text();
    }

    while (query.next()) {
        companies <<query.value(0).toString();
    }
    companyModel = new QStringListModel(companies, this);

    // Persons
    setevikModel = new QSqlRelationalTableModel(setevikTable);
    setevikModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    setevikModel->setTable("setevik");

    setevikModel->setHeaderData(setevikModel->fieldIndex("name"), Qt::Horizontal, tr("Name"));

    if (!setevikModel->select()) {
        QMessageBox::critical(this, "Unable to setup model",
                              "Error creating Setevik table model: " + setevikModel->lastError().text());
        return;
    }
}

void SetevikDB::setupUItoDB() {

    // Companies
    companyComboBox->setModel(companyModel);

    // Persons
    setevikTable->setModel(setevikModel);
    delegate = new QSqlRelationalDelegate(setevikTable);
    setevikTable->setItemDelegate(delegate);
    setevikTable->setColumnHidden(setevikModel->fieldIndex("id"), true);
    setevikTable->setColumnHidden(setevikModel->fieldIndex("company"), true);
    setevikTable->setColumnHidden(setevikModel->fieldIndex("vk"), true);
    setevikTable->setColumnHidden(setevikModel->fieldIndex("story"), true);
    setevikTable->setSelectionMode(QAbstractItemView::SingleSelection);
    setevikTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    setevikTable->resizeColumnsToContents();
    if (setevikModel->rowCount() > 0) {
        setevikTable->selectRow(0);
    }

    mapper = new QDataWidgetMapper();
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(setevikModel);
    mapper->setItemDelegate(delegate);
    connect(setevikTable->selectionModel(), &QItemSelectionModel::currentRowChanged,
            mapper, &QDataWidgetMapper::setCurrentModelIndex);
    connect(setevikTable->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &SetevikDB::updateDetails);
    updateDetails(setevikTable->selectionModel()->currentIndex());
}

void SetevikDB::showNewSetevikDialog() {
    auto *newSetevikDialog = new NewSetevikDialog(this, "Add new Setevik");
    if (newSetevikDialog->exec()) {

        int rowCount = setevikModel->rowCount();
        setevikModel->insertRows(rowCount, 1);

        setevikModel->setData(setevikModel->index(rowCount, 1), newSetevikDialog->nameLineEdit->text());
        setevikModel->setData(setevikModel->index(rowCount, 2), newSetevikDialog->vkLineEdit->text());
        setevikModel->setData(setevikModel->index(rowCount, 3), newSetevikDialog->storyTextEdit->toPlainText());
        setevikModel->setData(setevikModel->index(rowCount, 4), newSetevikDialog->companyComboBox->currentIndex());

        setevikModel->submitAll();
    }
}

void SetevikDB::showEditSetevikDialog() {

    int rowToEdit = mapper->currentIndex();

    auto *editSetevikDialog = new NewSetevikDialog(this, "Edit Setevik");
    editSetevikDialog->nameLineEdit->setText(setevikModel->record(rowToEdit).value("name").toString());
    editSetevikDialog->vkLineEdit->setText(setevikModel->record(rowToEdit).value("vk").toString());
    editSetevikDialog->storyTextEdit->setText(setevikModel->record(rowToEdit).value("story").toString());
    editSetevikDialog->companyComboBox->setCurrentIndex(setevikModel->record(rowToEdit).value("company").toInt());

    if (editSetevikDialog->exec()) {

        setevikModel->setData(setevikModel->index(rowToEdit, 1), editSetevikDialog->nameLineEdit->text());
        setevikModel->setData(setevikModel->index(rowToEdit, 2), editSetevikDialog->vkLineEdit->text());
        setevikModel->setData(setevikModel->index(rowToEdit, 3), editSetevikDialog->storyTextEdit->toPlainText());
        setevikModel->setData(setevikModel->index(rowToEdit, 4), editSetevikDialog->companyComboBox->currentIndex());

        setevikModel->submitAll();
    }

}

void SetevikDB::deleteSetevik() {
    QMessageBox::StandardButton deleteDialog;
    deleteDialog = QMessageBox::question(this, "Delete Setevik", "Are you sure?",
                          QMessageBox::Yes|QMessageBox::No);

    if (deleteDialog == QMessageBox::Yes) {

        int rowToDelete = mapper->currentIndex();

        if (!setevikModel->removeRow(rowToDelete)) {
            QMessageBox::critical(this, "Unable to delete item",
                                  "Error deleting item: " + setevikModel->lastError().text());
            return;
        }

        setevikModel->submitAll();
        mapper->submit();

        mapper->setCurrentIndex(qMax(0, rowToDelete-1));
        setevikTable->selectRow(qMax(0, rowToDelete-1));

    }

}

void SetevikDB::copySetevikVK() {

}

void SetevikDB::updateDetails(const QModelIndex &index) {
    int indexRow = index.row();
    nameLineEdit->setText(setevikModel->record(indexRow).value("name").toString());
    companyLineEdit->setText(setevikModel->record(indexRow).value("company").toString());
    vkLineEdit->setText(setevikModel->record(indexRow).value("vk").toString());
    storyTextEdit->setText(setevikModel->record(indexRow).value("story").toString());
}
