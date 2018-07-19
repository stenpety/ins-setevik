#include "mainwindow.h"
#include "initsetevikdb.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("Viva Setevo!"));
    createUI();
    createMenu();

    // Init databases
    initiSetevikDB(SETEVIKDBFILE);
}

MainWindow::~MainWindow() {}

void MainWindow::createUI() {
    auto *content = new QWidget();
    setCentralWidget(content);

    auto *layoutMain = new QVBoxLayout();
    content->setLayout(layoutMain);

    closePublicButton = new QPushButton(tr("Close public"));
    closePublicButton->setEnabled(false);
    connect(closePublicButton, &QPushButton::clicked, this, &MainWindow::showClosePublic);
    layoutMain->addWidget(closePublicButton);

    setevikDBButton = new QPushButton(tr("Setevik DB"));
    setevikDBButton->setEnabled(true);
    connect(setevikDBButton, &QPushButton::clicked, this, &MainWindow::showSetevikDB);
    layoutMain->addWidget(setevikDBButton);

    setevikTimerButton = new QPushButton(tr("Setevik Timer"));
    setevikTimerButton->setEnabled(true);
    connect(setevikTimerButton, &QPushButton::clicked, this, &MainWindow::showSetevikTimer);
    layoutMain->addWidget(setevikTimerButton);

}

void MainWindow::createMenu() {
    setevoMenu = menuBar()->addMenu(tr("&Setevo"));

    closePublicAct = new QAction(tr("Close public"), this);
    closePublicAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    setevoMenu->addAction(closePublicAct);
    connect(closePublicAct, &QAction::triggered, this, &MainWindow::showClosePublic);

    setevikDBAct = new QAction(tr("Setevik DB"), this);
    setevikDBAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    setevoMenu->addAction(setevikDBAct);
    connect(setevikDBAct, &QAction::triggered, this, &MainWindow::showSetevikDB);

    setevikTimerAct = new QAction(tr("Setevik Timer"), this);
    setevikTimerAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    setevoMenu->addAction(setevikTimerAct);
    connect(setevikTimerAct, &QAction::triggered, this, &MainWindow::showSetevikTimer);

    managementMenu = menuBar()->addMenu(tr("Management"));

    companiesAct = new QAction(tr("MLM Companies"));
    companiesAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    managementMenu->addAction(companiesAct);
    connect(companiesAct, &QAction::triggered, this, &MainWindow::showCompaniesMgmt);

    aboutMenu = menuBar()->addMenu(tr("About"));

    aboutAct = new QAction(tr("About"));
    aboutMenu->addAction(aboutAct);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::showAbout);
}


void MainWindow::showClosePublic() {


}

void MainWindow::showSetevikDB() {

    auto *setevikDB = new SetevikDB();
    setevikDB->show();
}

void MainWindow::showSetevikTimer() {

    auto *setevikTimer = new SetevikTimer(this);
    setevikTimer->show();
}

void MainWindow::showCompaniesMgmt() {
    auto *companiesMgmt = new CompaniesMgmt();
    companiesMgmt->show();
}

void MainWindow::showAbout() {
    auto *about = new About(this);
    about->show();
}
