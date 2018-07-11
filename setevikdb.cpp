#include "setevikdb.h"

SetevikDB::SetevikDB(QWidget *parent) : QWidget(parent) {

    setWindowTitle("Setevo Personalities");
    createUI();

    setupDb();
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

void SetevikDB::setupDb() {

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
}

void SetevikDB::setupUItoDB() {

    // Companies
    companyComboBox->setModel(companyModel);
}

void SetevikDB::showNewSetevikDialog() {
    auto *newSetevikDialog = new NewSetevikDialog(this);
    if (newSetevikDialog->exec()) {
        //TODO: add new setevik to dn logic
    }
}

void SetevikDB::showEditSetevikDialog() {

}

void SetevikDB::deleteSetevik() {


}

void SetevikDB::copySetevikVK() {

}
