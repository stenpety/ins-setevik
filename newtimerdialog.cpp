#include "newtimerdialog.h"

NewTimerDialog::NewTimerDialog(QWidget *parent, const QString &title) : QDialog(parent) {
    setWindowTitle(title);
    createUI();
}

void NewTimerDialog::createUI() {

    auto *layoutMain = new QHBoxLayout();

    auto *dismissButton = new QPushButton(tr("Dismiss"));
    connect(dismissButton, &QPushButton::clicked, this, &NewTimerDialog::dismissWindow);
    layoutMain->addWidget(dismissButton);

    setLayout(layoutMain);
}

void NewTimerDialog::dismissWindow() {
    this->hide();
}
