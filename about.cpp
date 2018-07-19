#include "about.h"

About::About(QWidget *parent) : QDialog(parent) {
    setWindowTitle("About INS <<Setevik>>");
    createUI();
}

void About::createUI() {
    auto *layoutMain = new QGridLayout();

    auto *companyLabel = new QLabel("KangaSoft");
    companyLabel->setAlignment(Qt::AlignHCenter);
    layoutMain->addWidget(companyLabel, 0, 0);

    auto *madeInLabel = new QLabel("Proudly made in Melbourne, Australia");
    madeInLabel->setAlignment(Qt::AlignCenter);
    layoutMain->addWidget(madeInLabel, 1, 0);

    auto *yearLabel = new QLabel("2018");
    yearLabel->setAlignment(Qt::AlignCenter);
    layoutMain->addWidget(yearLabel, 2, 0);

    setLayout(layoutMain);
}
