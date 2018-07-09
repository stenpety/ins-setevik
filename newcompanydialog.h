#ifndef NEWCOMPANYDIALOG_H
#define NEWCOMPANYDIALOG_H

#include <QWidget>
#include <QtWidgets>

class NewCompanyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewCompanyDialog(QWidget *parent = nullptr);

signals:

private:
    void createUI();

public slots:

private slots:

public:
    QLineEdit *nameLineEdit;
    QLineEdit *vkLineEdit;
    QLineEdit *keyWordLineEdit;

    QPushButton *submitButton;
    QPushButton *cancelButton;

private:

};

#endif // NEWCOMPANYDIALOG_H
