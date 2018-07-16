#include "seteviktimer.h"

SetevikTimer::SetevikTimer(QWidget *parent) : QMainWindow(parent) {
    createUI();


}

void SetevikTimer::createUI() {

    auto *content = new QWidget();
    setCentralWidget(content);

    setMinimumSize(320, 240);
    setWindowTitle("Setevik Timer");

    auto *layoutMain = new QGridLayout;

    auto *test = new QLabel("TEST");
    layoutMain->addWidget(test, 0, 0);


    dismissButton = new QPushButton(tr("Dismiss"));
    dismissButton->setMaximumWidth(100);
    connect(dismissButton, &QPushButton::clicked, this, &SetevikTimer::dismissWindow);
    layoutMain->addWidget(dismissButton, 1, 1);

    content->setLayout(layoutMain);

}

void SetevikTimer::dismissWindow() {
    this->hide();
}
