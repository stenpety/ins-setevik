#include "newtimerdialog.h"

NewTimerDialog::NewTimerDialog(QWidget *parent, const QString &title) : QDialog(parent) {
    setWindowTitle(title);
    createUI();
}

void NewTimerDialog::createUI() {

    auto *layoutMain = new QHBoxLayout();

    auto layoutLeft = new QVBoxLayout();

    // table and new setevik button

    auto layoutRight = new QGridLayout();

    // Buttons - 4-1
    auto *layoutButtons = new QHBoxLayout();

    auto *submitButton = new QPushButton(tr("Submit"));
    submitButton->setEnabled(false);
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);
    layoutButtons->addWidget(submitButton);

    auto *cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    layoutButtons->addWidget(cancelButton);

    layoutRight->addLayout(layoutButtons, 4, 1);

    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutRight);
    setLayout(layoutMain);
}
