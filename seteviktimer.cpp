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

void SetevikTimer::showNewTimerDialog() {
    auto newTimerDialog = new NewTimerDialog(this, "New Timer");
    newTimerDialog->exec();
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
