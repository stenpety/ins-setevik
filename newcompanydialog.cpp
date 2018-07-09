#include "newcompanydialog.h"

NewCompanyDialog::NewCompanyDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add new MLM company");
    createUI();
}

void NewCompanyDialog::createUI() {

    auto *layoutMain = new QVBoxLayout();
    setLayout(layoutMain);

    auto *layoutName = new QHBoxLayout();
    auto *nameLabel = new QLabel(tr("Company name: "));
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("MLM International");
    layoutName->addWidget(nameLabel);
    layoutName->addWidget(nameLineEdit);
    layoutMain->addLayout(layoutName);

    auto *layoutVK = new QHBoxLayout();
    auto *vkLabel = new QLabel(tr("VK main group: "));
    vkLineEdit = new QLineEdit();
    vkLineEdit->setPlaceholderText("mlm_intl");
    layoutVK->addWidget(vkLabel);
    layoutVK->addWidget(vkLineEdit);
    layoutMain->addLayout(layoutVK);

    auto *layoutKeyWord = new QHBoxLayout();
    auto *keyWordLabel = new QLabel(tr("Keyword: "));
    keyWordLineEdit = new QLineEdit();
    keyWordLineEdit->setPlaceholderText("mlm");
    layoutKeyWord->addWidget(keyWordLabel);
    layoutKeyWord->addWidget(keyWordLineEdit);
    layoutMain->addLayout(layoutKeyWord);

    auto *layoutButtons = new QHBoxLayout();
    submitButton = new QPushButton(tr("Submit"));
    submitButton->setEnabled(true);
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);
    layoutButtons->addWidget(submitButton);

    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    layoutButtons->addWidget(cancelButton);
    layoutMain->addLayout(layoutButtons);

}
