#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include <classes.h>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

    int registerAccount(QString login, QString password, QString company, int role = 0);

    int authAccount(QString login, QString password);

    QString encryptPassword(QString password);

    bool stringIsOkay(QString s);

    bool logpassIsOkay(QString s);

    bool loginIsFree(QString s);

private:
    Array <Account> accounts;
    bool isRegistration = false;

signals:
    void authClosed(int id);

private slots:
    void on_authEnterButton_clicked();

    void on_registrationButton_clicked();

    void reject();


private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
