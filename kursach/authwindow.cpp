#include "authwindow.h"
#include "mainwindow.h"
#include "ui_authwindow.h"
#include "classes.h"
#include "authorization.h"
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

}

AuthWindow::~AuthWindow()
{
    delete ui;
}

bool isRegistration = false;





void AuthWindow::on_authEnterButton_clicked()
{
    QString company = ui->companyLine->text();
    QString login = ui->loginLine->text();
    QString password = ui->passwordLine->text();
    if (!isRegistration){
        if (login == "" || password == ""){
            QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Все поля должны быть заполнены!");
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
        if (login == "" || password == "" || company == ""){
            QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Все поля должны быть заполнены!");
        } else {
            int accId = registerAccount(company, login, password, true);
            if (accId != -1){
                emit authClosed(accId);
                this->accept();
            } else {
                QMessageBox::critical(ui->authCentralWidget, "Ошибка", "Данный аккаунт уже существует!");
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
