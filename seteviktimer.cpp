#include "seteviktimer.h"

SetevikTimer::SetevikTimer(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Setevik Timer");
    createUI();


}

void SetevikTimer::createUI() {

    auto *content = new QWidget();
    setCentralWidget(content);

    setMinimumSize(320, 240);

    auto *layoutMain = new QGridLayout;

    // 0-0
    auto *layoutButtons = new QHBoxLayout();

    auto *newButton = new QPushButton(tr("New Timer"));
    connect(newButton, &QPushButton::clicked, this, &SetevikTimer::showNewTimerDialog);
    layoutButtons->addWidget(newButton);

    auto *editButton = new QPushButton(tr("Edit Timer"));
    connect(editButton, &QPushButton::clicked, this, &SetevikTimer::showEditTimerDialog);
    layoutButtons->addWidget(editButton);

    auto *deleteButton = new QPushButton(tr("Delete Timer"));
    connect(deleteButton, &QPushButton::clicked, this, &SetevikTimer::deleteTimer);
    layoutButtons->addWidget(deleteButton);

    layoutMain->addLayout(layoutButtons, 0, 0);

    // 1-0
    auto timerTable = new QTableView();
    layoutMain->addWidget(timerTable, 1, 0);

    // 2-0
    dismissButton = new QPushButton(tr("Dismiss"));
    dismissButton->setMaximumWidth(100);
    connect(dismissButton, &QPushButton::clicked, this, &SetevikTimer::dismissWindow);
    layoutMain->setAlignment(Qt::AlignRight);
    layoutMain->addWidget(dismissButton, 2, 0);

    content->setLayout(layoutMain);

}

void SetevikTimer::setupDbModels() {

    timerModel = new QSqlRelationalTableModel(timerTable);
    timerModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    timerModel->setTable("timers");

    // "CREATE TABLE timers (id INTEGER PRIMARY KEY, name INTEGER, start_date INTEGER, duration INTEGER, description TEXT, penalty TEXT)"
    timerModel->setHeaderData(timerModel->fieldIndex("name"), Qt::Horizontal, tr("Setevik"));
    timerModel->setHeaderData(timerModel->fieldIndex("start_date"), Qt::Horizontal, tr("Start Date"));
    timerModel->setHeaderData(timerModel->fieldIndex("duration"), Qt::Horizontal, tr("Duration"));
    timerModel->setHeaderData(timerModel->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    timerModel->setHeaderData(timerModel->fieldIndex("penalty"), Qt::Horizontal, tr("Penalty"));

    if (!timerModel->select()) {
        QMessageBox::critical(this, "Unable to setup TIMER model",
                              "Error creating Timer table model: " + timerModel->lastError().text());
        return;
    }

}

void SetevikTimer::setupUItoDB() {

}

void SetevikTimer::showNewTimerDialog() {
    auto newTimerDialog = new NewTimerDialog(this, "New Timer");

    if (newTimerDialog->exec()) {
        /*
        int rowCount = setevikModel->rowCount();
        setevikModel->insertRows(rowCount, 1);

        setevikModel->setData(setevikModel->index(rowCount, 1), newSetevikDialog->nameLineEdit->text() );
        setevikModel->setData(setevikModel->index(rowCount, 2), newSetevikDialog->vkLineEdit->text() );
        setevikModel->setData(setevikModel->index(rowCount, 3), newSetevikDialog->storyTextEdit->toPlainText() );
        setevikModel->setData(setevikModel->index(rowCount, 4), newSetevikDialog->getCompanyId() );

        if (!setevikModel->submitAll()) {
            QMessageBox::critical(this, "Unable to create new Setevik",
                                  "Error creating Setevik: " + setevikModel->lastError().text());
            return;
            */
        }

}

void SetevikTimer::showEditTimerDialog() {
    auto editTimerDialog = new NewTimerDialog(this, "Edit Timer");
    editTimerDialog->exec();
}

void SetevikTimer::deleteTimer() {

}

void SetevikTimer::dismissWindow() {
    this->hide();
}
