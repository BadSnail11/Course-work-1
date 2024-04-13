#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QCryptographicHash>

QString encryptPassword(QString password){
    QByteArray bytePassword = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Sha256);
    QString hashPassword = bytePassword.toHex();
    return hashPassword;
}

int authAccount(QString login, QString password){
    QFile file("./files/accounts.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonArray accArray = doc.object()["accounts"].toArray();
    for (const auto &value: accArray) {
        if (value.isObject()){
            Account acc(value.toObject());
            if (login == acc.getLogin() && encryptPassword(password) == acc.getPassword()){
                return acc.getId();
            }
        }
    }
    return -1;
}

int registerAccount(QString company, QString login, QString password, bool admin = false){
    QFile fileIn("./files/accounts.json");
    fileIn.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = fileIn.readAll();
    fileIn.close();

    QJsonDocument docIn = QJsonDocument::fromJson(val.toUtf8());
    QJsonArray accArray = docIn.object()["accounts"].toArray();
    for (const auto &value: accArray) {
        if (value.isObject()){
            Account acc(value.toObject());
            if (acc.getLogin() == login){
                return -1;
            }
        }
    }
    QJsonObject obj;
    QJsonObject accNew;
    int id = accArray.size();
    accNew.insert("id", QJsonValue::fromVariant(id));
    accNew.insert("admin", QJsonValue::fromVariant(admin));
    accNew.insert("company", QJsonValue::fromVariant(company));
    accNew.insert("login", QJsonValue::fromVariant(login));
    accNew.insert("password", QJsonValue::fromVariant(encryptPassword(password)));
    accArray.append(accNew);
    obj.insert("accounts", accArray);

    QJsonDocument docOut(obj);
    QString jsonString = docOut.toJson(QJsonDocument::Indented);
    QFile fileOut("./files/accounts.json");
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&fileOut);
    stream << jsonString;
    fileOut.close();
    return id;
}


#endif // AUTHORIZATION_H
