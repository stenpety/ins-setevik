#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QtWidgets>

class About : public QDialog {

    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);

private:
    void createUI();

signals:

public slots:

};

#endif // ABOUT_H
