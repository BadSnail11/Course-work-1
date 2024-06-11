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
#include <QStandardItemModel>
#include <QCheckBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Manager");
    ui->accountsButton->hide();
    ui->sortOBox->hide();
    ui->sortPBox->hide();
    ui->sortTBox->hide();
    ui->findEdit->hide();
    ui->findButton->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
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
    this->accounts.setArr(Array <Account> ().getArr());
    this->currentAccount = accounts.get(id);
    if (currentAccount.getRole() != 0)
    {
        ui->accountsButton->show();
    }
    else
    {
        ui->accountsButton->hide();
    }
    for (Passage pas: this->passages.getArr())
    {
        if (!dateIsOkay(pas.getDate()))
        {
            for (Order order: this->orders.getArr())
            {
                if (order.getPassageId() == pas.getId())
                {
                    order.setPassageId(0);
                    this->orders.set(order.getId(), order);
                }
            }
            this->passages.pop(pas.getId());
        }
    }
    this->orders.save();
    this->passages.save();
    on_ordersButton_clicked();
}

bool MainWindow::numberIsOkay(QString s)
{
    s = s.simplified().trimmed();
    if (s == "")
        return false;
    bool ok;
    int a = s.toInt(&ok);
    return (ok && a > 0);
}

bool MainWindow::stringIsOkay(QString s)
{
    s = s.simplified().trimmed();
    for (QChar c: s)
    {
        if (c.isDigit())
        {
            return false;
        }
    }
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s.at(i) == ' ')
        {
            count++;
        }
        else
        {
            count = 0;
        }
        if (count > 1)
            return false;
    }
    return !(s == "");
}

bool MainWindow::dateIsOkay(QString s)
{
    s = s.simplified().trimmed();
    QStringList list = s.split('.');
    if (list.size() != 3)
    {
        return false;
    }
    int day = list[0].toInt();
    int month = list[1].toInt();
    int year = list[2].toInt();
    QDate date(year, month, day);
    QDate current_date = QDate::currentDate();
    if (date > current_date)
    {
        return true;
    }
    return false;
}

void MainWindow::on_ordersButton_clicked()
{
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    ui->tableView->setModel(this->orders.OrdersModel(this->currentAccount.getCompany()));
    ui->tableView->setAccessibleName("orders");
    ui->tableView->update();
    ui->sortOBox->show();
    ui->sortPBox->hide();
    ui->sortTBox->hide();
    ui->orderButton->show();
    ui->addButton->show();
    ui->findEdit->hide();
    ui->findButton->hide();
    on_sortOBox_activated(ui->sortOBox->currentIndex());
}


void MainWindow::on_passagesButton_clicked()
{
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    ui->tableView->setModel(this->passages.PassagesModel());
    ui->tableView->setAccessibleName("passages");
    ui->tableView->update();
    ui->sortPBox->show();
    ui->sortOBox->hide();
    ui->sortTBox->hide();
    ui->orderButton->show();
    ui->addButton->show();
    ui->findEdit->hide();
    ui->findButton->hide();
    on_sortPBox_activated(ui->sortPBox->currentIndex());
}


void MainWindow::on_transportsButton_clicked()
{
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    ui->tableView->setModel(this->transports.TransportsModel());
    ui->tableView->setAccessibleName("transports");
    ui->tableView->update();
    ui->sortTBox->show();
    ui->sortOBox->hide();
    ui->sortPBox->hide();
    ui->orderButton->show();
    ui->addButton->show();
    ui->findEdit->hide();
    ui->findButton->hide();
    on_sortTBox_activated(ui->sortTBox->currentIndex());
}


void MainWindow::on_accountsButton_clicked()
{
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    ui->tableView->setModel(this->accounts.AccountsModel(currentAccount, ""));
    ui->tableView->setAccessibleName("accounts");
    ui->tableView->update();
    ui->sortOBox->hide();
    ui->sortPBox->hide();
    ui->sortTBox->hide();
    ui->orderButton->show();
    ui->orderButton->hide();
    ui->addButton->hide();
    ui->findEdit->show();
    ui->findButton->show();
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString tableName = ui->tableView->accessibleName();
    QModelIndex idIndex = ui->tableView->model()->index(index.row(), 0);
    int id = ui->tableView->model()->itemData(idIndex).first().toInt();
    if (tableName == "orders")
    {
        on_ordersButton_clicked();
        Order current_order = this->orders.get(id);
        QPushButton* button = current_order.getEditWidget(ui->infoWidget);
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_order_change_accepted);
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                   on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
    else if (tableName == "passages")
    {
        on_passagesButton_clicked();
        Passage current_passage = this->passages.get(id);
        int passage_id = current_passage.getId();
        if (current_passage.getWaypoints().empty())
        {
            current_passage.addWaypoint("", 0);
        }
        if (currentAccount.getRole() == 0)
        {
            current_passage.getLookWidget(ui->infoWidget);
            return;
        }
        auto obj = current_passage.getEditWidget(ui->infoWidget);
        QPushButton* button = obj.first;
        QList <QPair <QPushButton*, QPushButton*>>* list = obj.second;
        for (int i = 0; i < list->size(); i++)
        {
            auto o = list->at(i);
            QPushButton* plus = o.first;
            QPushButton* minus = o.second;
            QString name = plus->objectName();
            QObject::connect(plus, &QPushButton::clicked, [this, name, passage_id](){
                on_plus_clicked(name, passage_id);
            });
            QObject::connect(minus, &QPushButton::clicked, [this, name, passage_id](){
                on_minus_clicked(name, passage_id);
            });
        }
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_passage_change_accepted);
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                    on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
    else if (tableName == "transports")
    {
        on_transportsButton_clicked();
        if (currentAccount.getRole() == 0)
        {
            return;
        }
        Transport current_transport = this->transports.get(id);
        QPushButton* button = current_transport.getEditWidget(ui->infoWidget);

        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_transport_change_accepted);
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                    on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
    else if (tableName == "accounts")
    {
        on_accountsButton_clicked();
        Account current_account = this->accounts.get(id);
        if (current_account.getRole() == 2)
        {
            return;
        }
        if (current_account.getRole() == 1 && currentAccount.getRole() == 1)
        {
            return;
        }
        QPushButton* button = current_account.getEditWidget(ui->infoWidget, this->currentAccount.getRole());
        if (currentAccount.getRole() == 2)
        {
            button->setShortcut(Qt::Key_Return);
            QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_account_change_accepted);
        }
        else
        {
            button->hide();
        }
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                    on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
}

void MainWindow::on_order_change_accepted()
{
    auto list = ui->infoWidget->children().toList();
    Order current_order;
    if (this->orders.exists(list[1]->objectName().toInt()))
    {
        current_order = this->orders.get(list[1]->objectName().toInt());
    }
    else
    {
        current_order.setId(this->orders.getUniqueId());
        current_order.setCompany(this->currentAccount.getCompany());
    }
    QString name;
    QLineEdit* value;
    bool WeightError = false;
    bool Empty = false;
    bool PassageError = false;
    for (auto* obj: list)
    {
        name = obj->objectName();
        if (name == "cargo")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!stringIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_order.setCargo(value->text().simplified().trimmed());
            }
        }
        else if (name == "weight")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (this->passages.exists(qobject_cast <QLineEdit*> (list[6]->children().toList()[1])->text().toInt()))
            {
                Passage passage = this->passages.get(qobject_cast <QLineEdit*> (list[6]->children().toList()[1])->text().toInt());
                if (!numberIsOkay(value->text()))
                {
                    Empty = true;
                }
                else if (value->text().toInt() + passage.getWeight() - current_order.getWeight() > passage.getTransportCapacity())
                {
                    WeightError = true;
                }
                else
                {
                    current_order.setWeight(value->text().simplified().trimmed().toInt());
                }
            }
            else
            {
                current_order.setWeight(value->text().simplified().trimmed().toInt());
            }
        }
        else if (name == "departure")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!stringIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_order.setDeparture(value->text().simplified().trimmed());
            }
        }
        else if (name == "destination")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!stringIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_order.setDestination(value->text().simplified().trimmed());
            }
        }
        else if (name == "passageId")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (numberIsOkay(value->text()))
            {
                if (this->passages.exists(value->text().trimmed().toInt()))
                {
                    Passage passage = this->passages.get(qobject_cast <QLineEdit*> (list[6]->children().toList()[1])->text().toInt());
                    if (qobject_cast <QLineEdit*> (list[3]->children().toList()[1])->text().toInt() + passage.getWeight() - current_order.getWeight() > passage.getTransportCapacity())
                    {
                        WeightError = true;
                    }
                    else
                    {
                        current_order.setPassageId(value->text().simplified().trimmed().toInt());
                    }
                }
                else
                {
                    PassageError = true;
                    current_order.setPassageId(0);
                }
            }
            else
            {
                current_order.setPassageId(0);
            }
        }
    }
    if (Empty)
    {
        QMessageBox::critical(this, "Ошибка", "Поля не должны быть пустыми, а строки не содержать цифр!");
    }
    else if (WeightError)
    {
        QMessageBox::critical(this, "Ошибка", "Транспорт перегружен!");
    }
    else if (PassageError)
    {
        QMessageBox::critical(this, "Ошибка", "Данного рейса не сущетсвует!");
    }
    if (Empty || WeightError || PassageError)
    {
        while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
            delete w;
        QPushButton* button = current_order.getEditWidget(ui->infoWidget);
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_order_change_accepted);
    }
    else
    {
        if (this->orders.exists(current_order.getId()))
        {
            this->orders.set(current_order.getId(), current_order);
        }
        else
        {
            this->orders.add(current_order);
        }
        orders.save();
        on_ordersButton_clicked();
    }
}

void MainWindow::on_passage_change_accepted()
{
    auto list = ui->infoWidget->children().toList();
    Passage current_passage;
    if (this->passages.exists(list[1]->objectName().toInt()))
    {
        current_passage = this->passages.get(list[1]->objectName().toInt());
    }
    else
    {
        current_passage.setId(this->passages.getUniqueId());
        current_passage.addWaypoint("", 0);
    }
    QString name;
    QLineEdit* value;
    bool Empty = false;
    bool TransportError = false;
    bool Date = false;
    for (auto* obj: list)
    {
        name = obj->objectName();
        if (name == "transportId")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!numberIsOkay(value->text()))
            {
                current_passage.setTransportId(0);
            }
            else
            {
                if (this->transports.exists(value->text().toInt()))
                {
                    current_passage.setTransportId(value->text().simplified().trimmed().toInt());
                }
                else
                {
                    TransportError = true;
                }
            }
        }
        else if (name == "date")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!dateIsOkay(value->text()))
            {
                Date = true;
            }
            else
            {
                current_passage.setDate(value->text().simplified().trimmed());
            }
        }
    }
    if (Empty || Date || TransportError)
    {
        if (Empty)
        {
            QMessageBox::critical(this, "Ошибка", "Поля не должны быть пустыми, а строки не содержать цифр!");
        }
        else if (Date)
        {
            QMessageBox::critical(this, "Ошибка", "Неверная дата!");
        }
        else if (TransportError)
        {
            QMessageBox::critical(this, "Ошибка", "Данного транспорта не существует!");
        }
        int passage_id = current_passage.getId();
        while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
            delete w;
        auto obj = current_passage.getEditWidget(ui->infoWidget);
        QPushButton* button = obj.first;
        QList <QPair <QPushButton*, QPushButton*>>* list = obj.second;
        for (int i = 0; i < list->size(); i++)
        {
            auto o = list->at(i);
            QPushButton* plus = o.first;
            QPushButton* minus = o.second;
            QString name = plus->objectName();
            QObject::connect(plus, &QPushButton::clicked, [this, name, passage_id](){
                on_plus_clicked(name, passage_id);
            });
            QObject::connect(minus, &QPushButton::clicked, [this, name, passage_id](){
                on_minus_clicked(name, passage_id);
            });
        }
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_passage_change_accepted);
    }
    else
    {
        QList <QString> points;
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "point")
            {
                QLineEdit* point = qobject_cast <QLineEdit*> (w);
                if (stringIsOkay(point->text()))
                {
                    points.append(point->text().simplified().trimmed());
                }
            }
        }
        current_passage.setWaypoints(points);
        current_passage.countCost(this->transports);
        if (this->passages.exists(current_passage.getId()))
        {
            this->passages.set(current_passage.getId(), current_passage);
        }
        else
        {
            this->passages.add(current_passage);
        }
        passages.save();
        on_passagesButton_clicked();
    }
}

void MainWindow::on_transport_change_accepted()
{
    auto list = ui->infoWidget->children().toList();
    Transport current_transport;
    if (this->transports.exists(list[1]->objectName().toInt()))
    {
        current_transport = this->transports.get(list[1]->objectName().toInt());
    }
    else
    {
        current_transport.setId(this->transports.getUniqueId());
    }
    QString name;
    bool Empty = false;
    bool NotFree = false;
    for (Passage pas: this->passages.getArr())
    {
        if (pas.getTransportId() == current_transport.getId())
        {
            NotFree = true;
        }
    }
    QLineEdit* value;
    for (auto* obj: list)
    {
        name = obj->objectName();
        if (name == "type")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!stringIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_transport.setType(value->text().simplified().trimmed());
            }
        } else if (name == "capacity")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!numberIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_transport.setCapacity(value->text().simplified().trimmed().toInt());
            }
        } else if (name == "consumption")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!numberIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_transport.setConsumption(value->text().simplified().trimmed().toInt());
            }
        }
    }
    if (Empty || NotFree)
    {
        if (NotFree)
        {
            QMessageBox::critical(this, "Ошибка", "Нельзя изменить транспорт, пока он закреплен за рейсом!");
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Поля не должны быть пустыми, а строки не содержать цифр!");
        }
        while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
            delete w;
        QPushButton* button = current_transport.getEditWidget(ui->infoWidget);
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_transport_change_accepted);
    }
    else
    {
        if (this->transports.exists(current_transport.getId()))
        {
            this->transports.set(current_transport.getId(), current_transport);
        }
        else
        {
            this->transports.add(current_transport);
        }
        transports.save();
        QList <Passage> list = this->passages.getArr();
        for (Passage pas: list)
        {
            pas.countCost(this->transports);
            this->passages.set(pas.getId(), pas);
        }
        // this->passages.setArr(list);
        this->passages.save();
        on_transportsButton_clicked();
    }
}

void MainWindow::on_account_change_accepted()
{
    auto list = ui->infoWidget->children().toList();
    Account current_account = this->accounts.get(list[1]->objectName().toInt());
    QString name;
    bool Empty = false;
    QLineEdit* value;
    QCheckBox* check;
    for (auto* obj: list)
    {
        name = obj->objectName();
        if (name == "company")
        {
            value = qobject_cast <QLineEdit*> (obj->children().toList()[1]);
            if (!stringIsOkay(value->text()))
            {
                Empty = true;
            }
            else
            {
                current_account.setCompany(value->text().simplified().trimmed());
            }
        } else if (name == "admin")
        {
            check = qobject_cast <QCheckBox*> (obj->children().toList()[1]);
            if (check->isChecked())
            {
                current_account.setRole(1);
            }
            else
            {
                current_account.setRole(0);
            }
        }
    }
    if (Empty)
    {
        QMessageBox::critical(this, "Ошибка", "Поля не должны быть пустыми, а строки не содержать цифр!");
        while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
            delete w;
        QPushButton* button = current_account.getEditWidget(ui->infoWidget, currentAccount.getRole());
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_account_change_accepted);
    }
    else
    {
        this->accounts.set(current_account.getId(), current_account);
        this->accounts.save();
        on_accountsButton_clicked();

    }
}

void MainWindow::on_plus_clicked(QString idx, int id)
{
    Passage current_passage;
    if (this->passages.exists(id))
    {
        current_passage = this->passages.get(id);
    }
    else
    {
        current_passage.setId(id);
    }
    QList <QString> points;
    for (auto* w: ui->infoWidget->findChildren<QWidget*>())
    {
        if (w->objectName() == "point")
        {
            QLineEdit* point = qobject_cast <QLineEdit*> (w);
            points.append(point->text());
        }
    }
    current_passage.setWaypoints(points);
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    current_passage.addWaypoint("", idx.toInt());
    if (this->passages.exists(id))
    {
        this->passages.set(id, current_passage);
    }
    on_passagesButton_clicked();
    int passage_id = current_passage.getId();
    auto obj = current_passage.getEditWidget(ui->infoWidget);
    QPushButton* button = obj.first;
    QList <QPair <QPushButton*, QPushButton*>>* list = obj.second;
    for (int i = 0; i < list->size(); i++)
    {
        auto o = list->at(i);
        QPushButton* plus = o.first;
        QPushButton* minus = o.second;
        QString name = plus->objectName();
        QObject::connect(plus, &QPushButton::clicked, [this, name, passage_id](){
            on_plus_clicked(name, passage_id);
        });
        QObject::connect(minus, &QPushButton::clicked, [this, name, passage_id](){
            on_minus_clicked(name, passage_id);
        });
    }
    button->setShortcut(Qt::Key_Return);
    QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_passage_change_accepted);
}

void MainWindow::on_minus_clicked(QString idx, int id)
{
    Passage current_passage;
    if (this->passages.exists(id))
    {
        current_passage = this->passages.get(id);
    }
    else
    {
        current_passage.setId(id);
    }
    QList <QString> points;
    for (auto* w: ui->infoWidget->findChildren<QWidget*>())
    {
        if (w->objectName() == "point")
        {
            QLineEdit* point = qobject_cast <QLineEdit*> (w);
            points.append(point->text());
        }
    }
    current_passage.setWaypoints(points);
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    current_passage.deleteWaypoint(idx.toInt());
    if (this->passages.exists(id))
    {
        this->passages.set(id, current_passage);
    }
    on_passagesButton_clicked();
    int passage_id = current_passage.getId();
    if (current_passage.getWaypoints().empty())
    {
        current_passage.addWaypoint("", 0);
    }
    auto obj = current_passage.getEditWidget(ui->infoWidget);
    QPushButton* button = obj.first;
    QList <QPair <QPushButton*, QPushButton*>>* list = obj.second;
    for (int i = 0; i < list->size(); i++)
    {
        auto o = list->at(i);
        QPushButton* plus = o.first;
        QPushButton* minus = o.second;
        QString name = plus->objectName();
        QObject::connect(plus, &QPushButton::clicked, [this, name, passage_id](){
            on_plus_clicked(name, passage_id);
        });
        QObject::connect(minus, &QPushButton::clicked, [this, name, passage_id](){
            on_minus_clicked(name, passage_id);
        });
    }
    button->setShortcut(Qt::Key_Return);
    QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_passage_change_accepted);
}

void MainWindow::on_addButton_clicked()
{
    QString tableName = ui->tableView->accessibleName();
    if (tableName == "orders")
    {
        on_ordersButton_clicked();
        Order current_order;
        current_order.setId(this->orders.getUniqueId());
        current_order.setCompany(this->currentAccount.getCompany());
        QPushButton* button = current_order.getEditWidget(ui->infoWidget);
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_order_change_accepted);
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                int id = this->orders.getUniqueId();
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                    on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
    else if (tableName == "transports")
    {
        on_transportsButton_clicked();
        Transport current_transport;
        current_transport.setId(this->transports.getUniqueId());
        QPushButton* button = current_transport.getEditWidget(ui->infoWidget);
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_transport_change_accepted);
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                int id = this->transports.getUniqueId();
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                    on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
    else
    {
        on_passagesButton_clicked();
        Passage current_passage;
        current_passage.setId(this->passages.getUniqueId());
        current_passage.addWaypoint("", 0);
        int passage_id = current_passage.getId();
        auto obj = current_passage.getEditWidget(ui->infoWidget);
        QPushButton* button = obj.first;
        QList <QPair <QPushButton*, QPushButton*>>* list = obj.second;
        for (int i = 0; i < list->size(); i++)
        {
            auto o = list->at(i);
            QPushButton* plus = o.first;
            QPushButton* minus = o.second;
            QString name = plus->objectName();
            QObject::connect(plus, &QPushButton::clicked, [this, name, passage_id](){
                on_plus_clicked(name, passage_id);
            });
            QObject::connect(minus, &QPushButton::clicked, [this, name, passage_id](){
                on_minus_clicked(name, passage_id);
            });
        }
        button->setShortcut(Qt::Key_Return);
        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_passage_change_accepted);
        for (auto* w: ui->infoWidget->findChildren<QWidget*>())
        {
            if (w->objectName() == "delete")
            {
                QPushButton* buttonDel = qobject_cast <QPushButton*> (w);
                int id = this->passages.getUniqueId();
                QObject::connect(buttonDel, &QPushButton::clicked, [this, id, tableName](){
                    on_deleteButton_clicked(tableName, id);
                });
            }
        }
    }
}

void MainWindow::on_deleteButton_clicked(QString type, int id)
{
    if (type == "orders")
    {
        if (this->orders.exists(id))
        {
            this->orders.pop(id);
            this->orders.save();
        }
        on_ordersButton_clicked();
    }
    else if (type == "transports")
    {
        if (this->transports.exists(id))
        {
            bool f = false;
            for (Passage pas: this->passages.getArr())
            {
                if (pas.getTransportId() == id)
                {
                    f = true;
                    break;
                }
            }
            if (!f)
            {
                this->transports.pop(id);
                this->transports.save();
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Нельзя удалить транспорт, пока он закреплен за рейсом!");
            }
        }
        on_transportsButton_clicked();
    }
    else if (type == "passages")
    {
        if (this->passages.exists(id))
        {
            for (Order order: this->orders.getArr())
            {
                if (order.getPassageId() == id)
                {
                    order.setPassageId(0);
                    this->orders.set(order.getId(), order);
                }
            }
            this->orders.save();
            this->passages.pop(id);
            this->passages.save();
        }
        on_passagesButton_clicked();
    }
    else if (type == "accounts")
    {
        if (this->accounts.exists(id))
        {
            this->accounts.pop(id);
            this->accounts.save();
        }
        on_accountsButton_clicked();
    }
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
}



void MainWindow::on_sortOBox_activated(int index)
{
    switch (index) {
    case 0:
        orders.sort([](Order a, Order b){return Order().compareById(a, b);});
        break;
    case 1:
        orders.sort([](Order a, Order b){return Order().compareByCargo(a, b);});
        break;
    case 2:
        orders.sort([](Order a, Order b){return Order().compareByWeight(a, b);});
        break;
    default:
        break;
    }
    this->orders.save();
    ui->tableView->setModel(this->orders.OrdersModel(this->currentAccount.getCompany()));
    ui->tableView->setAccessibleName("orders");
    ui->tableView->update();
    ui->sortOBox->show();
    ui->sortPBox->hide();
    ui->sortTBox->hide();
    ui->orderButton->setText("Порядок по возрастанию");
}


void MainWindow::on_sortTBox_activated(int index)
{
    switch (index) {
    case 0:
        transports.sort([](Transport a, Transport b){return Transport().compareById(a, b);});
        break;
    case 1:
        transports.sort([](Transport a, Transport b){return Transport().compareByType(a, b);});
        break;
    case 2:
        transports.sort([](Transport a, Transport b){return Transport().compareByCapacity(a, b);});
        break;
    case 3:
        transports.sort([](Transport a, Transport b){return Transport().compareByConsumption(a, b);});
        break;
    default:
        break;
    }
    this->transports.save();
    ui->tableView->setModel(this->transports.TransportsModel());
    ui->tableView->setAccessibleName("transports");
    ui->tableView->update();
    ui->sortTBox->show();
    ui->sortOBox->hide();
    ui->sortPBox->hide();
    ui->orderButton->setText("Порядок по возрастанию");
}


void MainWindow::on_sortPBox_activated(int index)
{
    switch (index) {
    case 0:
        passages.sort([](Passage a, Passage b){return Passage().compareById(a, b);});
        break;
    case 1:
        passages.sort([](Passage a, Passage b){return Passage().compareByCost(a, b);});
        break;
    case 2:
        passages.sort([](Passage a, Passage b){return Passage().compareByDate(a, b);});
        break;
    default:
        break;
    }
    this->passages.save();
    ui->tableView->setModel(this->passages.PassagesModel());
    ui->tableView->setAccessibleName("passages");
    ui->tableView->update();
    ui->sortPBox->show();
    ui->sortOBox->hide();
    ui->sortTBox->hide();
    ui->orderButton->setText("Порядок по возрастанию");
}

void MainWindow::on_orderButton_clicked()
{
    QString name = ui->tableView->accessibleName();
    if (name == "orders")
    {
        orders.reverse();
        orders.save();
        ui->tableView->setModel(this->orders.OrdersModel(this->currentAccount.getCompany()));
        ui->tableView->setAccessibleName("orders");
        ui->tableView->update();
        ui->sortOBox->show();
        ui->sortPBox->hide();
        ui->sortTBox->hide();
    }
    else if (name == "transports")
    {
        transports.reverse();
        transports.save();
        ui->tableView->setModel(this->transports.TransportsModel());
        ui->tableView->setAccessibleName("transports");
        ui->tableView->update();
        ui->sortTBox->show();
        ui->sortOBox->hide();
        ui->sortPBox->hide();
    }
    else if (name == "passages")
    {
        passages.reverse();
        passages.save();
        ui->tableView->setModel(this->passages.PassagesModel());
        ui->tableView->setAccessibleName("passages");
        ui->tableView->update();
        ui->sortPBox->show();
        ui->sortOBox->hide();
        ui->sortTBox->hide();
    }
    if (ui->orderButton->text() == "Порядок по возрастанию")
    {
        ui->orderButton->setText("Порядок по убыванию");
    }
    else
    {
        ui->orderButton->setText("Порядок по возрастанию");
    }
}




void MainWindow::on_logoutButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Выйти из аккаунта?");
    msgBox.setWindowTitle("Confirm");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        AuthWindow auth;
        QObject::connect(&auth, &AuthWindow::authClosed, this, &MainWindow::on_auth_closed);
        auth.setModal(true);
        auth.exec();
    }
}


void MainWindow::on_findButton_clicked()
{
    QString find_text = ui->findEdit->text().trimmed();
    while ( QWidget* w = ui->infoWidget->findChild<QWidget*>() )
        delete w;
    ui->tableView->setModel(this->accounts.AccountsModel(currentAccount, find_text));
    if (ui->tableView->model()->rowCount() == 0)
    {
        ui->tableView->setModel(this->accounts.AccountsModel(currentAccount, ""));
        QMessageBox::critical(this, "Ошибка", "Пользователь не найден!");
    }
    ui->tableView->setAccessibleName("accounts");
    ui->tableView->update();
    ui->sortOBox->hide();
    ui->sortPBox->hide();
    ui->sortTBox->hide();
    ui->orderButton->show();
    ui->orderButton->hide();
    ui->addButton->hide();
    ui->findEdit->show();
    ui->findButton->show();
}
