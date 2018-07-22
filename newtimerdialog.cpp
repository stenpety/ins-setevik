#include "newtimerdialog.h"

NewTimerDialog::NewTimerDialog(QWidget *parent, const QString &title) : QDialog(parent) {
    setWindowTitle(title);

    mapper = new QDataWidgetMapper();
    createUI();

    setupModel();
    setupUItoDB();
}

void NewTimerDialog::createUI() {

    auto *layoutMain = new QHBoxLayout();
    setLayout(layoutMain);

    auto *layoutLeft = new QVBoxLayout();

    setevikTable = new QTableView();
    layoutLeft->addWidget(setevikTable);

    newSetevikButton = new QPushButton(tr("New Setevik"));
    connect(newSetevikButton, &QPushButton::clicked, this, &NewTimerDialog::showNewSetevikDialog);
    layoutLeft->addWidget(newSetevikButton);

    auto layoutRight = new QVBoxLayout;

    // Start date
    auto *layoutStartDate = new QHBoxLayout();
    auto *startDateLabel = new QLabel("Start Date");
    startDateLineEdit = new QLineEdit();
    layoutStartDate->addWidget(startDateLabel);
    layoutStartDate->addWidget(startDateLineEdit);
    layoutRight->addLayout(layoutStartDate);

    // Duration
    auto *layoutDuration = new QHBoxLayout();
    auto *durationLabel = new QLabel("Duration");
    durationLineEdit = new QLineEdit();
    layoutDuration->addWidget(durationLabel);
    layoutDuration->addWidget(durationLineEdit);
    layoutRight->addLayout(layoutDuration);

    // Description
    auto *layoutDescription = new QHBoxLayout();
    auto *descriptionLabel = new QLabel("Description");
    descriptionTextEdit = new QTextEdit();
    layoutDescription->addWidget(descriptionLabel);
    layoutDescription->addWidget(descriptionTextEdit);
    layoutRight->addLayout(layoutDescription);

    // Penalty
    auto *layoutPenalty = new QHBoxLayout();
    auto *penaltyLabel = new QLabel("Penalty");
    penaltyTextEdit = new QTextEdit();
    layoutPenalty->addWidget(penaltyLabel);
    layoutPenalty->addWidget(penaltyTextEdit);
    layoutRight->addLayout(layoutPenalty);

    // Buttons - 4-1
    auto *layoutButtons = new QHBoxLayout();

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setEnabled(false);
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);
    layoutButtons->addWidget(submitButton);

    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    layoutButtons->addWidget(cancelButton);

    layoutRight->addLayout(layoutButtons);

    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutRight);

}

void NewTimerDialog::setupModel() {
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

void NewTimerDialog::setupUItoDB() {

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
    setevikTable->horizontalHeader()->setStretchLastSection(true);


    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(setevikModel); // causes error
    mapper->setItemDelegate(delegate);
    connect(setevikTable->selectionModel(), &QItemSelectionModel::currentRowChanged, mapper, &QDataWidgetMapper::setCurrentModelIndex);
}

void NewTimerDialog::showNewSetevikDialog() {

}

void NewTimerDialog::activateSubmitButton() {
    submitButton->setEnabled(true);
}
