#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QStandardItemModel>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QTableView>
#include <QListView>
#include <QListWidget>
#include <QScrollBar>
#include <QCheckBox>
#include <cmath>


class Object
{
private:
    QJsonObject values;
public:
    Object () {}
    Object(QJsonObject values)
    {
        this->values = values;
    }
    void setValues(QJsonObject values)
    {
        this->values = values;
    }
    QJsonObject getValues()
    {
        return this->values;
    }
    int getId()
    {
        return values["id"].toInt();
    }
    void setId(int id)
    {
        this->values["id"] = id;
    }
    virtual QString getFileName()
    {
        return "None";
    }
    QWidget* getEditLineWidget(QString label, QString line, QString OName)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(widget);
        QLineEdit* line_w = new QLineEdit(widget);
        QLabel* label_w = new QLabel(widget);
        line_w->setObjectName(line);
        label_w->setFixedWidth(75);
        line_w->setText(line);
        label_w->setText(label);
        layout->addWidget(label_w);
        layout->addWidget(line_w);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setObjectName(OName);
        return widget;
    }
    QList <QString> JArrToLst(QJsonArray JArray)
    {
        QList <QString> list;
        for (auto o: JArray)
        {
            list.push_back(o.toString());
        }
        return list;
    }
    QJsonArray LstToJArr(QList <QString> list)
    {
        QJsonArray JArray;
        for (auto o: list)
        {
            JArray.append(o);
        }
        return JArray;
    }
    int compareById(Object a, Object b){
        if (a.getId() < b.getId()){
            return -1;
        } else if (a.getId() > b.getId()){
            return 1;
        } else {
            return 0;
        }
    }
};


template <typename T = Object>
class Array
{
private:
    QList <T> array;
    QList <T> qSortAlogorythm(QList <T> list, int size, int compare(T, T), int i = 0)
    {
        int j = i + size - 1;
        T mid = list.value(i + size / 2);
        do {
            while (compare(list.value(i), mid) < 0){
                i++;
            }
            while (compare(list.value(j), mid) > 0){
                j--;
            }
            if (i <= j){
                list.swapItemsAt(i, j);
                i++;
                j--;
            }
        } while (i <= j);
        if (j > 0){
            list = qSortAlogorythm(list, j + 1, compare);
        }
        if (i < size){
            list = qSortAlogorythm(list, size - i, compare, i);
        }
        return list;
    }
    QList <T> mergeAlgotythm(QList <T> list, int p, int q, int r, int compare(T, T))
    {
        int n1 = q - p + 1;
        int n2 = r - q;
        QList <T> L(n1);
        QList <T> M(n2);
        for (int i = 0; i < n1; i++)
            L[i] = list[p + i];
        for (int j = 0; j < n2; j++)
            M[j] = list[q + 1 + j];
        int i = 0, j = 0, k = p;
        while (i < n1 && j < n2)
        {
            if (compare(L[i], M[j]) <= 0)
            {
                list[k] = L[i];
                i++;
            }
            else
            {
                list[k] = M[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            list[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            list[k] = M[j];
            j++;
            k++;
        }
        return list;
    }
    QList <T> mSortAlgorythm(QList <T> list, int l, int r, int compare(T, T))
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;
            list = mSortAlgorythm(list, l, m, compare);
            list = mSortAlgorythm(list, m + 1, r, compare);
            list = mergeAlgotythm(list, l, m, r, compare);
        }
        return list;
    }
    QList <T> iSortAlgorythm(QList <T> list, int size, int compare(T, T))
    {
        for (int step = 1; step < size; step++)
        {
            T key = list[step];
            int j = step - 1;
            while (j >= 0 && compare(key, list[j]) < 0)
            {
                list[j + 1] = list[j];
                --j;
            }
            list[j + 1] = key;
        }
        return list;
    }

public:
    Array()
    {
        QString fileName = T().getFileName();
        QString name = "./files/";
        name.append(fileName);
        name.append(".json");
        QFile file(name);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray arr = doc.object()[fileName].toArray();
        for (const auto &value: arr)
        {
            if (value.isObject())
            {
                array.push_back(T(value.toObject()));
            }
        }
    }
    void save(){
        QJsonArray jsonArray;
        QJsonObject obj;
        for(T o: array){
            QJsonObject currentObj;
            jsonArray.append(o.getValues());
        }
        QString fileName = T().getFileName();
        QString name = "./files/";
        name.append(fileName);
        name.append(".json");
        obj.insert(fileName, jsonArray);
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QFile file(name);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << jsonString;
        file.close();
    }
    QList <T> getArr()
    {
        return this->array;
    }
    void setArr(QList <T> array)
    {
        this->array = array;
    }
    int getUniqueId()
    {
        int id = 1;
        for (T obj: this->array)
        {
            if (obj.getId() >= id)
            {
                id = obj.getId() + 1;
            }
        }
        return id;
    }
    void add(T object)
    {
        this->array.push_back(object);
    }
    void pop(int id)
    {
        int idx;
        for (int i = 0; i < this->array.size(); i++)
        {
            if (this->array[i].getId() == id)
            {
                idx = i;
                break;
            }
        }
        this->array.removeAt(idx);
    }
    void sort(int compare(T, T))
    {
        int size = this->array.size();
        if (size < 10)
        {
            this->array = this->qSortAlogorythm(this->array, size, compare);
        }
        else if (size < 50)
        {
            this->array = this->iSortAlgorythm(this->array, size, compare);
        }
        else
        {
            this->array = this->mSortAlgorythm(this->array, 0, size - 1, compare);
        }
    }
    void reverse()
    {
        std::reverse(this->array.begin(), this->array.end());
    }
    T get(int id)
    {
        for (T obj: this->array)
        {
            if (obj.getId() == id)
            {
                return obj;
            }
        }
    }
    void set(int id, T object)
    {
        for (int i = 0; i < this->array.size(); i++)
        {
            if (this->array[i].getId() == id)
            {
                this->array[i] = object;
                break;
            }
        }
    }
    bool exists(int id)
    {
        for (auto obj: this->array)
        {
            if (obj.getId() == id)
            {
                return true;
            }
        }
        return false;
    }
    T binarySearch(T obj, int compare(T, T))
    {
        this->array = this->qSortAlogorythm(this->array, this->array.size(), compare);
        int mid, l = 0, r = this->array.size() - 1;
        while (l <= r)
        {
            mid = (l + r) / 2;
            int comp = compare(obj, this->array[mid]);
            if (comp == 0)
            {
                return this->array[mid];
            }
            else if (comp > 0)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return this->array[mid];
    }
    int levenstein(QString a, QString b)
    {
        int n = a.size(), m = b.size();
        if (n > m)
        {
            int tmp;
            QString tmp_s;
            tmp = n;
            n = m;
            m = tmp;
            tmp_s = a;
            a = b;
            b = tmp_s;
        }
        QList <int> curr_row(n + 1);
        for (int i = 1; i <= m; i++)
        {
            QList <int> prev_row = curr_row;
            curr_row[0] = i;
            for (int j = 1; j <= n; j++)
            {
                if (a.at(j - 1) != b.at(i - 1))
                {
                    curr_row[j] = qMin(qMin(prev_row[j] + 1, curr_row[j - 1] + 1), prev_row[j - 1] + 1);
                }
                else
                {
                    curr_row[j] = qMin(qMin(prev_row[j] + 1, curr_row[j - 1] + 1), prev_row[j - 1]);
                }
            }
        }
        return curr_row[n];
    }
    QStandardItemModel* AccountsModel(T account, QString find)
    {
        if (find != "")
        {
            QStandardItemModel* model = new QStandardItemModel(1, 4);
            model->setHorizontalHeaderLabels({"№ аккаунта", "Компания", "Логин", "Роль"});
            T obj;
            obj.setLogin(find);
            obj = binarySearch(obj, [](T a, T b){return T().compareByLogin(a, b);});
            if (obj.getLogin() != find)
            {
                model = new QStandardItemModel(0, 4);
                model->setHorizontalHeaderLabels({"№ Аккаунта", "Компания", "Логин", "Роль"});
                return model;
            }
            model->setData(model->index(0, 0), obj.getId());
            model->setData(model->index(0, 1), obj.getCompany());
            model->setData(model->index(0, 2), obj.getLogin());
            if (obj.getRole() == 2)
            {
                model->setData(model->index(0, 3), "Суперадмин");
            }
            else if (obj.getRole() == 1)
            {
                model->setData(model->index(0, 3), "Админ");
            }
            else
            {
                model->setData(model->index(0, 3), "Менеджер");
            }
            for (int i = 0; i < 4; i++)
            {
                model->item(0, i)->setEditable(false);
            }
            return model;
        }
        int rows = 0;
        for (int i = 0; i < this->array.size(); i++)
        {
            T obj = this->array[i];
            if (account.getRole() == 2 || account.getCompany() == obj.getCompany())
            {
                rows++;
            }
        }
        QStandardItemModel* model = new QStandardItemModel(rows, 4);
        model->setHorizontalHeaderLabels({"№ аккаунта", "Компания", "Логин", "Роль"});
        int row = 0;
        for (int i = 0; i < this->array.size(); i++)
        {
            T obj = this->array[i];
            if (account.getRole() != 2 && account.getCompany() != obj.getCompany())
            {
                continue;
            }
            model->setData(model->index(row, 0), obj.getId());
            model->setData(model->index(row, 1), obj.getCompany());
            model->setData(model->index(row, 2), obj.getLogin());
            if (obj.getRole() == 2)
            {
                model->setData(model->index(row, 3), "Суперадмин");
            }
            else if (obj.getRole() == 1)
            {
                model->setData(model->index(row, 3), "Админ");
            }
            else
            {
                model->setData(model->index(row, 3), "Менеджер");
            }
            for (int i = 0; i < 4; i++)
            {
                model->item(row, i)->setEditable(false);
            }
            row++;
        }
        return model;
    }
    QStandardItemModel* OrdersModel(QString company)
    {
        int rows = 0;
        for (int i = 0; i < this->array.size(); i++)
        {
            if (company == "admin" || this->array[i].getCompany() == company)
            {
                rows++;
            }
        }
        QStandardItemModel* model = new QStandardItemModel(rows, 6);
        model->setHorizontalHeaderLabels({"№ заказа", "Груз", "Масса, кг", "Отправление", "Назначение", "№ рейса"});
        int row = 0;
        for (int i = 0; i < this->array.size(); i++)
        {
            T obj = this->array[i];
            if (company != "admin" && obj.getCompany() != company)
            {
                continue;
            }
            model->setData(model->index(row, 0), obj.getId());
            model->setData(model->index(row, 1), obj.getCargo());
            model->setData(model->index(row, 2), obj.getWeight());
            model->setData(model->index(row, 3), obj.getDeparture());
            model->setData(model->index(row, 4), obj.getDestination());
            if (obj.getPassageId() == 0)
            {
                model->setData(model->index(row, 5), "-");
            }
            else
            {
                model->setData(model->index(row, 5), obj.getPassageId());
            }
            for (int i = 0; i < 6; i++)
            {
                model->item(row, i)->setEditable(false);
            }
            row++;
        }
        return model;
    }
    QStandardItemModel* PassagesModel()
    {
        QStandardItemModel* model = new QStandardItemModel(this->array.size(), 4);
        model->setHorizontalHeaderLabels({"№ рейса", "№ транспорта", "Дата отправления", "Стоимость, руб."});
        int row = 0;
        for (int i = 0; i < this->array.size(); i++)
        {
            T obj = this->array[i];
            model->setData(model->index(row, 0), obj.getId());
            if (obj.getTransportId() == 0)
            {
                model->setData(model->index(row, 1), "-");
            }
            else
            {
                model->setData(model->index(row, 1), obj.getTransportId());
            }
            model->setData(model->index(row, 2), obj.getDate());
            model->setData(model->index(row, 3), obj.getCost());
            for (int i = 0; i < 4; i++)
            {
                model->item(row, i)->setEditable(false);
            }
            row++;
        }
        return model;
    }
    QStandardItemModel* TransportsModel()
    {
        QStandardItemModel* model = new QStandardItemModel(this->array.size(), 4);
        model->setHorizontalHeaderLabels({"№ транспорта", "Тип", "Грузоподъёмность", "Расход, руб./пункт"});
        int row = 0;
        for (int i = 0; i < this->array.size(); i++)
        {
            T obj = this->array[i];
            model->setData(model->index(row, 0), obj.getId());
            model->setData(model->index(row, 1), obj.getType());
            model->setData(model->index(row, 2), obj.getCapacity());
            model->setData(model->index(row, 3), obj.getConsumption());
            for (int i = 0; i < 4; i++)
            {
                model->item(row, i)->setEditable(false);
            }
            row++;
        }
        return model;
    }
};

class Account : public Object
{
public:
    Account () : Object() {}
    Account (QJsonObject values) : Object (values) {}
    QString getLogin()
    {
        return getValues()["login"].toString();
    }
    void setLogin(QString login)
    {
        QJsonObject values = getValues();
        values["login"] = login;
        setValues(values);
    }
    QString getPassword()
    {
        return getValues()["password"].toString();
    }
    void setPassword(QString password)
    {
        QJsonObject values = getValues();
        values["password"] = password;
        setValues(values);
    }
    QString getCompany()
    {
        return getValues()["company"].toString();
    }
    void setCompany(QString company)
    {
        QJsonObject values = getValues();
        values["company"] = company;
        setValues(values);
    }
    int getRole()
    {
        return getValues()["role"].toInt();
    }
    void setRole(int role)
    {
        QJsonObject values = getValues();
        values["role"] = role;
        setValues(values);
    }
    QWidget* getSwitchLineWidget(QString label, int role, QString OName)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(widget);
        QCheckBox* box = new QCheckBox(widget);
        box->setObjectName(label);
        box->setText(label);
        if (role == 1)
        {
            box->setChecked(true);
        }
        layout->addWidget(box);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setObjectName(OName);
        return widget;
    }
    QPushButton* getEditWidget(QWidget* parent, int role)
    {
        delete parent->layout();
        QVBoxLayout *layout = new QVBoxLayout(parent);
        if (role == 2)
            layout->setContentsMargins(6, 6, 6, 400);
        else
            layout->setContentsMargins(6, 6, 6, 500);
        QLabel* label = new QLabel();
        QString label_text = "Аккаунт №";
        label_text.append(QString::number(getId()));
        label->setText(label_text);
        label->setAlignment(Qt::AlignHCenter);
        label->setObjectName(QString::number(getId()));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        layout->addWidget(label);
        if (role == 2)
        {
            layout->addWidget(getEditLineWidget("Компания", getCompany(), "company"));
            layout->addWidget(getSwitchLineWidget("Админ", getRole(), "admin"));
        }
        QPushButton* button = new QPushButton();
        button->setText("Принять изменения");
        layout->addWidget(button);
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Удалить");
        deleteButton->setObjectName("delete");
        layout->addWidget(deleteButton);
        return button;
    }
    int compareByLogin(Account a, Account b){
        return a.getLogin().compare(b.getLogin());
    }
    QString getFileName() override
    {
        return "accounts";
    }
};

class Order : public Object
{
public:
    Order () : Object() {}
    Order(QJsonObject values) : Object(values) {}
    QString getCargo()
    {
        return getValues()["cargo"].toString();
    }
    void setCargo(QString cargo)
    {
        QJsonObject values = getValues();
        values["cargo"] = cargo;
        setValues(values);
    }
    QString getCompany()
    {
        return getValues()["company"].toString();
    }
    void setCompany(QString company)
    {
        QJsonObject values = getValues();
        values["company"] = company;
        setValues(values);
    }
    QString getDeparture()
    {
        return getValues()["departure"].toString();
    }
    void setDeparture(QString departure)
    {
        QJsonObject values = getValues();
        values["departure"] = departure;
        setValues(values);
    }
    QString getDestination()
    {
        return getValues()["destination"].toString();
    }
    void setDestination(QString destination)
    {
        QJsonObject values = getValues();
        values["destination"] = destination;
        setValues(values);
    }
    int getWeight()
    {
        return getValues()["weight"].toInt();
    }
    void setWeight(int weight)
    {
        QJsonObject values = getValues();
        values["weight"] = weight;
        setValues(values);
    }
    int getPassageId()
    {
        return getValues()["passage"].toInt();
    }
    void setPassageId(int passage)
    {
        QJsonObject values = getValues();
        values["passage"] = passage;
        setValues(values);
    }

    QPushButton* getEditWidget(QWidget* parent)
    {
        delete parent->layout();
        QVBoxLayout *layout = new QVBoxLayout(parent);
        layout->setContentsMargins(6, 6, 6, 300);
        QLabel* label = new QLabel();
        QString label_text = "Заказ №";
        label_text.append(QString::number(getId()));
        label->setText(label_text);
        label->setAlignment(Qt::AlignHCenter);
        label->setObjectName(QString::number(getId()));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        layout->addWidget(label);
        layout->addWidget(getEditLineWidget("Груз", getCargo(), "cargo"));
        layout->addWidget(getEditLineWidget("Масса", QString::number(getWeight()), "weight"));
        layout->addWidget(getEditLineWidget("Отправление", getDeparture(), "departure"));
        layout->addWidget(getEditLineWidget("Назначение", getDestination(), "destination"));
        layout->addWidget(getEditLineWidget("№ рейса", QString::number(getPassageId()), "passageId"));
        QPushButton* button = new QPushButton();
        button->setText("Принять изменения");
        layout->addWidget(button);
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Удалить");
        deleteButton->setObjectName("delete");
        layout->addWidget(deleteButton);
        return button;
    }
    QString getFileName() override
    {
        return "orders";
    }
    int compareByWeight(Order a, Order b){
        if (a.getWeight() < b.getWeight()){
            return -1;
        } else if (a.getWeight() > b.getWeight()){
            return 1;
        } else {
            return 0;
        }
    }
    int compareByCargo(Order a, Order b){
        return a.getCargo().compare(b.getCargo());
    }
};


class Transport : public Object
{
public:
    Transport() : Object() {}
    Transport(QJsonObject values) : Object(values) {}
    int getCapacity()
    {
        return getValues()["capacity"].toInt();
    }
    void setCapacity(int capacity)
    {
        QJsonObject value = getValues();
        value["capacity"] = capacity;
        setValues(value);
    }
    int getConsumption()
    {
        return getValues()["consumption"].toInt();
    }
    void setConsumption(int consumption)
    {
        QJsonObject value = getValues();
        value["consumption"] = consumption;
        setValues(value);
    }
    QString getType()
    {
        return getValues()["type"].toString();
    }
    void setType(QString type)
    {
        QJsonObject value = getValues();
        value["type"] = type;
        setValues(value);
    }
    QPushButton* getEditWidget(QWidget* parent)
    {
        delete parent->layout();
        QVBoxLayout *layout = new QVBoxLayout(parent);
        layout->setContentsMargins(6, 6, 6, 400);
        QLabel* label = new QLabel();
        QString label_text = "Транспорт №";
        label_text.append(QString::number(getId()));
        label->setText(label_text);
        label->setAlignment(Qt::AlignHCenter);
        label->setObjectName(QString::number(getId()));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        layout->addWidget(label);
        layout->addWidget(getEditLineWidget("Тип", getType(), "type"));
        layout->addWidget(getEditLineWidget("Грузоподъёмность", QString::number(getCapacity()), "capacity"));
        layout->addWidget(getEditLineWidget("Расход", QString::number(getConsumption()), "consumption"));
        QPushButton* button = new QPushButton();
        button->setText("Принять изменения");
        layout->addWidget(button);
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Удалить");
        deleteButton->setObjectName("delete");
        layout->addWidget(deleteButton);
        return button;
    }
    QString getFileName() override
    {
        return "transports";
    }
    int compareByCapacity(Transport a, Transport b){
        if (a.getCapacity() < b.getCapacity()){
            return -1;
        } else if (a.getCapacity() > b.getCapacity()){
            return 1;
        } else {
            return 0;
        }
    }
    int compareByConsumption(Transport a, Transport b){
        if (a.getConsumption() < b.getConsumption()){
            return -1;
        } else if (a.getConsumption() > b.getConsumption()){
            return 1;
        } else {
            return 0;
        }
    }
    int compareByType(Transport a, Transport b){
        return a.getType().compare(b.getType());
    }
};

class Passage : public Object
{
public:
    Passage () : Object() {}
    Passage (QJsonObject values) : Object(values) {}
    QString getDate()
    {
        return getValues()["date"].toString();
    }
    void setDate(QString date)
    {
        QJsonObject value = getValues();
        value["date"] = date;
        setValues(value);
    }
    int getTransportId()
    {
        return getValues()["transport"].toInt();
    }
    void setTransportId(int id)
    {
        QJsonObject value = getValues();
        value["transport"] = id;
        setValues(value);
    }
    int getTransportCapacity()
    {
        Array <Transport> array;
        if (array.exists(getTransportId()))
        {
            Transport transport = array.get(getTransportId());
            return transport.getCapacity();
        }
        else
        {
            return 0;
        }
    }
    int getCost()
    {
        return getValues()["cost"].toInt();
    }
    void setCost(int cost)
    {
        QJsonObject value = getValues();
        value["cost"] = cost;
        setValues(value);
    }
    QList <QString> getWaypoints()
    {
        return JArrToLst(getValues()["waypoints"].toArray());
    }
    void setWaypoints(QList <QString> list)
    {
        QJsonObject value = getValues();
        value["waypoints"] = LstToJArr(list);
        setValues(value);
    }
    void addWaypoint(QString point, int i = -1)
    {
        QList <QString> ways = getWaypoints();
        ways.insert(i, point);
        setWaypoints(ways);
    }
    void deleteWaypoint(int i = 1)
    {
        QList <QString> ways = getWaypoints();
        ways.removeAt(i - 1);
        setWaypoints(ways);
    }
    Transport getTransport(Array <Transport> array)
    {
        return array.get(getTransportId());
    }
    void countCost(Array <Transport> array)
    {
        if (array.exists(getTransportId()))
        {
            Transport transport  = getTransport(array);
            setCost(transport.getConsumption() * getWaypoints().size());
        }
        else
        {
            setCost(0);
        }
    }
    void getLookLine(QVBoxLayout* parent, int pos, QString name)
    {
        QWidget* widget = new QWidget();
        widget->setObjectName(name);
        QHBoxLayout* layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        QLabel* label1 = new QLabel();
        QLabel* label2 = new QLabel();
        label1->setObjectName("point");
        label2->setText(QString::number(pos));
        label2->setMaximumWidth(20);
        label1->setText(name);
        label1->setStyleSheet("background-color: rgb(255, 255, 255);");
        layout->addWidget(label2);
        layout->addWidget(label1);
        parent->addWidget(widget);
    }
    void getLookWidget(QWidget* parent)
    {
        delete parent->layout();
        QVBoxLayout *layout = new QVBoxLayout(parent);
        layout->setContentsMargins(6, 6, 6, 400);
        QLabel* label = new QLabel();
        QString label_text = "Рейс №";
        label_text.append(QString::number(getId()));
        label->setText(label_text);
        label->setAlignment(Qt::AlignHCenter);
        label->setObjectName(QString::number(getId()));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        layout->addWidget(label);
        QScrollArea* area = new QScrollArea();
        QWidget* area_widget = new QWidget();
        QVBoxLayout* area_layout = new QVBoxLayout(area_widget);
        QList <QString> list = getWaypoints();
        for (int i = 0; i < list.size(); i++)
        {
            getLookLine(area_layout, i + 1, list[i]);
        }
        area->setWidget(area_widget);
        area->setWidgetResizable(true);
        area->setObjectName("points");
        layout->addWidget(area);
    }
    QPair <QPushButton*, QPushButton*> getPointWidget(QVBoxLayout* parent, int pos, QString name)
    {
        QWidget* widget = new QWidget();
        widget->setObjectName(name);
        QHBoxLayout* layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        QLabel* label = new QLabel();
        QLineEdit* line = new QLineEdit();
        QPushButton* plus = new QPushButton();
        QPushButton* minus = new QPushButton();
        plus->setObjectName(QString::number(pos));
        minus->setObjectName(QString::number(pos));
        line->setObjectName("point");
        label->setText(QString::number(pos));
        label->setMaximumWidth(20);
        line->setText(name);
        plus->setText("+");
        plus->setMaximumWidth(20);
        minus->setText("-");
        minus->setMaximumWidth(20);
        layout->addWidget(label);
        layout->addWidget(line);
        layout->addWidget(plus);
        layout->addWidget(minus);
        parent->addWidget(widget);
        return {plus, minus};
    }
    QPair <QPushButton*, QList <QPair <QPushButton*, QPushButton*>>*> getEditWidget(QWidget* parent)
    {
        delete parent->layout();
        QVBoxLayout *layout = new QVBoxLayout(parent);
        layout->setContentsMargins(6, 6, 6, 225);
        QLabel* label = new QLabel();
        QString label_text = "Рейс №";
        label_text.append(QString::number(getId()));
        label->setText(label_text);
        label->setAlignment(Qt::AlignHCenter);
        label->setObjectName(QString::number(getId()));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        layout->addWidget(label);
        layout->addWidget(getEditLineWidget("№ транспорта", QString::number(getTransportId()), "transportId"));
        layout->addWidget(getEditLineWidget("Дата", getDate(), "date"));
        QLabel* way = new QLabel();
        way->setText("Маршрут");
        way->setAlignment(Qt::AlignHCenter);
        layout->addWidget(way);
        QScrollArea* area = new QScrollArea();
        QWidget* area_widget = new QWidget();
        QVBoxLayout* area_layout = new QVBoxLayout(area_widget);
        QList <QString> list = getWaypoints();
        QList <QPair <QPushButton*, QPushButton*>>* list_buttons = new QList <QPair <QPushButton*, QPushButton*>>();
        QPair <QPushButton*, QPushButton*> plus_minus;
        for (int i = 0; i < list.size(); i++)
        {
            plus_minus = getPointWidget(area_layout, i+1, list[i]);
            list_buttons->append(plus_minus);

        }
        area->setWidget(area_widget);
        area->setWidgetResizable(true);
        area->setObjectName("points");
        layout->addWidget(area);
        QPushButton* button = new QPushButton();
        button->setText("Принять изменения");
        layout->addWidget(button);
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Удалить");
        deleteButton->setObjectName("delete");
        layout->addWidget(deleteButton);
        return {button, list_buttons};
    }
    int getWeight()
    {
        int count = 0;
        Array <Order> orders;
        for (Order order: orders.getArr())
        {
            if (order.getPassageId() == getId())
            {
                count += order.getWeight();
            }
        }
        return count;
    }
    QString getFileName() override
    {
        return "passages";
    }
    int compareByCost(Passage a, Passage b){
        if (a.getCost() < b.getCost()){
            return -1;
        } else if (a.getCost() > b.getCost()){
            return 1;
        } else {
            return 0;
        }
    }
    int compareByDate(Passage a, Passage b){
        return a.getDate().compare(b.getDate());
    }
};

#endif // CLASSES_H
