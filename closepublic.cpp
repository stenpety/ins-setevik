#include "closepublic.h"

ClosePublic::ClosePublic(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Close MLM public");
    createUI();

}

void ClosePublic::createUI() {

    setMinimumSize(320, 240);

    auto *layoutMain = new QGridLayout;

    auto *test = new QLabel("TEST");
    layoutMain->addWidget(test, 0, 0);

    dismissButton = new QPushButton(tr("Dismiss"));
    dismissButton->setMaximumWidth(100);
    connect(dismissButton, &QPushButton::clicked, this, &ClosePublic::dismissWindow);
    layoutMain->addWidget(dismissButton, 1, 1);

    setLayout(layoutMain);
}

void ClosePublic::dismissWindow() {
    this->hide();
}
