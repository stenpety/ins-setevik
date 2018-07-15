#include "newsetevikdialog.h"

NewSetevikDialog::NewSetevikDialog(QWidget *parent, const QString &title) : QDialog(parent) {
    // TODO: take title as parameter, used both for new and edit
    setWindowTitle(title);
    createUI();
}

int NewSetevikDialog::getCompanyId() const {

    QSqlQuery query;
    query.prepare("SELECT id FROM companies WHERE name = ?");
    query.addBindValue(companyComboBox->currentText());

    if (!query.exec()) {
        qWarning() << "Company ID query ERROR: " << query.lastError().text();
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}

void NewSetevikDialog::createUI() {
    auto *layoutMain = new QVBoxLayout();
    setLayout(layoutMain);

    auto *layoutName = new QHBoxLayout();
    auto *nameLabel = new QLabel(tr("Name: "));
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Setevik Leader");
    connect(nameLineEdit, &QLineEdit::textChanged, this, &NewSetevikDialog::activateSubmitButton);
    layoutName->addWidget(nameLabel);
    layoutName->addWidget(nameLineEdit);
    layoutMain->addLayout(layoutName);

    auto *layoutCompany = new QHBoxLayout();
    auto companyLabel = new QLabel(tr("Company: "));
    companyComboBox = new QComboBox();
    setupModel();
    companyComboBox->setModel(companyModel);
    layoutCompany->addWidget(companyLabel);
    layoutCompany->addWidget(companyComboBox);
    layoutMain->addLayout(layoutCompany);

    auto *layoutVK = new QHBoxLayout();
    auto *vkLabel = new QLabel(tr("VK profile: "));
    vkLineEdit = new QLineEdit();
    vkLineEdit->setPlaceholderText("setevik_1990");
    connect(vkLineEdit, &QLineEdit::textChanged, this, &NewSetevikDialog::activateSubmitButton);
    layoutVK->addWidget(vkLabel);
    layoutVK->addWidget(vkLineEdit);
    layoutMain->addLayout(layoutVK);

    auto *layoutStory = new QHBoxLayout();
    auto *storyLabel = new QLabel(tr("Story: "));
    storyTextEdit = new QTextEdit();
    storyTextEdit->setPlaceholderText("Destroyed his labour book");
    connect(storyTextEdit, &QTextEdit::textChanged, this, &NewSetevikDialog::activateSubmitButton);
    layoutStory->addWidget(storyLabel);
    layoutStory->addWidget(storyTextEdit);
    layoutMain->addLayout(layoutStory);

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
void NewSetevikDialog::activateSubmitButton() {
    submitButton->setEnabled((nameLineEdit->text().length() > 0) &&
                              (vkLineEdit->text().length() > 0) &&
                             (storyTextEdit->toPlainText().length() > 0));
}

void NewSetevikDialog::setupModel() {

    QStringList companies;
    QSqlQuery query;
    query.prepare("SELECT name FROM companies");
    if (!query.exec()) {
        qWarning() << "Companies query ERROR: " << query.lastError().text();
    }

    while (query.next()) {
        companies << query.value(0).toString();
    }
    companyModel = new QStringListModel(companies, this);
    companyModel->sort(1, Qt::AscendingOrder);
}
