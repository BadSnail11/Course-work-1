#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include "classes.h"
#include "algorythms.h"
#include "classeses.h"
#include <iostream>


int compareRequestsByWeight(Request a, Request b){
    if (a.getWeight() < b.getWeight()){
        return 1;
    } else if (a.getWeight() > b.getWeight()){
        return 0;
    } else {
        return -1;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_auth_closed(int id){
    if (id == -1){
        this->close();
        return;
    }
    Account currentAccount(id);
    // Files files;
    // files.requests.setArray(qSort(files.requests.getArray(), files.requests.getArray().size(), compareRequestsByWeight));
    // files.save();
}
