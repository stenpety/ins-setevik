#ifndef NEWSETEVIKDIALOG_H
#define NEWSETEVIKDIALOG_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class NewSetevikDialog : public QDialog {

    Q_OBJECT

public:
    explicit NewSetevikDialog(QWidget *parent = nullptr);

private:
    void createUI();

signals:

public slots:

private slots:
    void activateSubmitButton();

public:
    QLineEdit *nameLineEdit;
    QComboBox *companyComboBox;
    QLineEdit *vkLineEdit;
    QTextEdit *storyTextEdit;

    QPushButton *submitButton;
    QPushButton *cancelButton;

private:

};

#endif // NEWSETEVIKDIALOG_H
