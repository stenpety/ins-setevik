#include "companiesmgmt.h"

CompaniesMgmt::CompaniesMgmt(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MLM Companies");
    createUI();

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
        QSqlQuery query;
        query.prepare("INSERT INTO company(name, vk, keyWord)"
                      "VALUES (:name, :vk, :keyWord)");
        query.bindValue(":name", newCompanyDialog->nameLineEdit->text());
        query.bindValue(":vk", newCompanyDialog->vkLineEdit->text());
        query.bindValue(":keyWord", newCompanyDialog->keyWordLineEdit->text());
        if (!query.exec()) {
            qWarning() << "New company ERROR: " << query.lastError().text();
        }
    }
}
