#ifndef NEWSETEVIKDIALOG_H
#define NEWSETEVIKDIALOG_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

#include <iostream>

class NewSetevikDialog : public QDialog {

    Q_OBJECT

public:
    explicit NewSetevikDialog(QWidget *parent = nullptr,
                              const QString &title = "Add new");
    int getCompanyId() const;

private:
    void createUI();
    void setupModel();

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
    QStringListModel *companyModel;
};

#endif // NEWSETEVIKDIALOG_H
