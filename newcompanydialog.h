#ifndef NEWCOMPANYDIALOG_H
#define NEWCOMPANYDIALOG_H

#include <QWidget>
#include <QtWidgets>

class NewCompanyDialog : public QDialog {

    Q_OBJECT

public:
    explicit NewCompanyDialog(QWidget *parent = nullptr,
                              const QString &title = "Add new");

private:
    void createUI();

signals:

public slots:

private slots:
    void activateSubmitButton();

public:
    QLineEdit *nameLineEdit;
    QLineEdit *vkLineEdit;
    QLineEdit *keyWordLineEdit;

    QPushButton *submitButton;
    QPushButton *cancelButton;

private:

};

#endif // NEWCOMPANYDIALOG_H
