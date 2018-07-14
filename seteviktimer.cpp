#include "seteviktimer.h"

SetevikTimer::SetevikTimer(QWidget *parent) : QWidget(parent) {
    createUI();


}

void SetevikTimer::createUI() {

    setMinimumSize(640, 480);
    setWindowTitle("Setevik Timer");

    auto *layoutMain = new QGridLayout;

    auto *test = new QLabel("TEST");
    layoutMain->addWidget(test, 0, 0);


    dismissButton = new QPushButton(tr("Dismiss"));
    dismissButton->setMaximumWidth(100);
    connect(dismissButton, &QPushButton::clicked, this, &SetevikTimer::dismissWindow);
    layoutMain->addWidget(dismissButton, 1, 1);

    this->setLayout(layoutMain);

}

void SetevikTimer::dismissWindow() {
    this->hide();
}
