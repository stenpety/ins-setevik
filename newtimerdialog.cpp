#include "newtimerdialog.h"

NewTimerDialog::NewTimerDialog(QWidget *parent, const QString &title) : QDialog(parent) {
    setWindowTitle(title);
    createUI();
}

void NewTimerDialog::createUI() {

    auto *layoutMain = new QHBoxLayout();

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
    setLayout(layoutMain);
}

void NewTimerDialog::showNewSetevikDialog() {

}

void NewTimerDialog::activateSubmitButton() {
    submitButton->setEnabled(true);
}
