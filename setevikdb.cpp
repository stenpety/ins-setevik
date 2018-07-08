#include "setevikdb.h"

SetevikDB::SetevikDB(QWidget *parent) : QWidget(parent) {

    auto *layoutMain = new QVBoxLayout();
    setLayout(layoutMain);

    auto testLabel = new QLabel("TEST");
    layoutMain->addWidget(testLabel);

}
