#include "newcompanydialog.h"

NewCompanyDialog::NewCompanyDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add new MLM company");
    createUI();
}

// Private
void NewCompanyDialog::createUI() {

    auto *layoutMain = new QVBoxLayout();
    setLayout(layoutMain);

    auto *layoutName = new QHBoxLayout();
    auto *nameLabel = new QLabel(tr("Company name: "));
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("MLM International");
    connect(nameLineEdit, &QLineEdit::textChanged, this, &NewCompanyDialog::activateSubmitButton);
    layoutName->addWidget(nameLabel);
    layoutName->addWidget(nameLineEdit);
    layoutMain->addLayout(layoutName);

    auto *layoutVK = new QHBoxLayout();
    auto *vkLabel = new QLabel(tr("VK main group: "));
    vkLineEdit = new QLineEdit();
    vkLineEdit->setPlaceholderText("mlm_intl");
    connect(vkLineEdit, &QLineEdit::textChanged, this, &NewCompanyDialog::activateSubmitButton);
    layoutVK->addWidget(vkLabel);
    layoutVK->addWidget(vkLineEdit);
    layoutMain->addLayout(layoutVK);

    auto *layoutKeyWord = new QHBoxLayout();
    auto *keyWordLabel = new QLabel(tr("Keyword: "));
    keyWordLineEdit = new QLineEdit();
    keyWordLineEdit->setPlaceholderText("mlm");
    connect(keyWordLineEdit, &QLineEdit::textChanged, this, &NewCompanyDialog::activateSubmitButton);
    layoutKeyWord->addWidget(keyWordLabel);
    layoutKeyWord->addWidget(keyWordLineEdit);
    layoutMain->addLayout(layoutKeyWord);

    auto *layoutButtons = new QHBoxLayout();
    submitButton = new QPushButton(tr("Submit"));
    submitButton->setEnabled(false);
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);
    layoutButtons->addWidget(submitButton);

    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    layoutButtons->addWidget(cancelButton);
    layoutMain->addLayout(layoutButtons);

}

// Private Slots
void NewCompanyDialog::activateSubmitButton() {
    submitButton->setEnabled((nameLineEdit->text().length() > 0) &&
                              (vkLineEdit->text().length() > 0) &&
                             (keyWordLineEdit->text().length() > 0));
}
