#include "authwindow.h"
#include "mainwindow.h"
#include "ui_authwindow.h"
#include "classes.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCryptographicHash>

AuthWindow::AuthWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    ui->companyLine->hide();
    this->setWindowTitle("Login/Registration");
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

bool AuthWindow::stringIsOkay(QString s)
{
    s = s.simplified().trimmed();
    return !(s == "");
}

bool AuthWindow::logpassIsOkay(QString s)
{
    s = s.simplified().trimmed();
    if (s == "")
        return false;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

bool AuthWindow::loginIsFree(QString s)
{
    s = s.simplified().trimmed();
    for (Account acc: this->accounts.getArr())
    {
        if (acc.getLogin() == s)
            return false;
    }
    return free;
}

QString AuthWindow::encryptPassword(QString password)
{
    QByteArray bytePassword = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Sha256);
    QString hashPassword = bytePassword.toHex();
    return hashPassword;
}

int AuthWindow::authAccount(QString login, QString password)
{
    password = encryptPassword(password);
    for (Account acc: this->accounts.getArr())
    {
        if (password == acc.getPassword())
        {
            return acc.getId();
        }
    }
    return -1;
}

int AuthWindow::registerAccount(QString login, QString password, QString company, int role)
{
    if (!loginIsFree(login))
    {
        return -1;
    }
    Account acc;
    acc.setId(this->accounts.getUniqueId());
    acc.setLogin(login.trimmed());
    acc.setPassword(encryptPassword(password.trimmed()));
    acc.setCompany(company.trimmed());
    acc.setRole(role);
    this->accounts.add(acc);
    this->accounts.save();
    return acc.getId();
}

void AuthWindow::on_authEnterButton_clicked()
{
    QString company = ui->companyLine->text();
    QString login = ui->loginLine->text();
    QString password = ui->passwordLine->text();
    if (!isRegistration){
        if (!logpassIsOkay(login) || !logpassIsOkay(password)){
            QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Все поля должны быть заполнены и не содержать пробелов!");
        } else {
            int accId = authAccount(login, password);
            if (accId != -1){
                emit authClosed(accId);
                this->accept();
            } else {
                QMessageBox::warning(ui->authCentralWidget, "Ошибка", "Неверный логин или пароль!");
            }
        }
    } else {
        if (!logpassIsOkay(login) || !logpassIsOkay(password) || !stringIsOkay(company))
        {
            QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Все поля должны быть заполнены и не содержать пробелов!");
        }
        else if (company.trimmed() == "admin")
        {
            QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Вы не можете использовать название компании 'admin'!");
        }
        else
        {
            int accId = registerAccount(login, password, company);
            if (accId != -1){
                emit authClosed(accId);
                this->accept();
            } else {
                QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Данный логин уже занят!");
            }
        }
    }
}


void AuthWindow::on_registrationButton_clicked()
{
    if (!isRegistration){
        ui->companyLine->show();
        isRegistration = true;
        ui->registrationButton->setText("Назад");
        ui->authLabel->setText("Регистрация");
        ui->authEnterButton->setText("Зарегистрироваться");
        ui->authEnterButton->setShortcut(Qt::Key_Return);
        ui->passwordLine->setEchoMode(QLineEdit::Normal);
        ui->loginLine->clear();
        ui->passwordLine->clear();
    } else {
        ui->companyLine->hide();
        isRegistration = false;
        ui->registrationButton->setText("Зарегистрироваться");
        ui->authLabel->setText("Авторизация");
        ui->authEnterButton->setText("Войти");
        ui->authEnterButton->setShortcut(Qt::Key_Return);
        ui->passwordLine->setEchoMode(QLineEdit::Password);
    }
}


void AuthWindow::reject(){
    emit authClosed(-1);
    QDialog::reject();
}
