#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>

// class Object {
// private:
//     int id;
// };

class Account {
private:
    int id;
    QString company;
    QString login;
    QString password;
public:
    Account (QJsonObject obj){
        this->id = obj["id"].toInt();
        this->company = obj["company"].toString();
        this->login = obj["login"].toString();
        this->password = obj["password"].toString();
    }
    Account (int id){
        QFile file("./files/accounts.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray requestArray = doc.object()["accounts"].toArray();
        QJsonObject obj;
        for (const auto &value: requestArray) {
            if (value.isObject() && value.toObject()["id"].toInt() == id){
                obj = value.toObject();
                this->id = obj["id"].toInt();
                this->company = obj["company"].toString();
                this->login = obj["login"].toString();
                this->password = obj["password"].toString();
                break;
            }
        }
    }
    int getId(){ return id; }
    QString getCompany(){ return company; }
    QString getLogin(){ return login; }
    QString getPassword(){ return password; }
};

class Request
{
private:
    int id;
    int clientId;
    QString cargo;
    int weight;
    QString departure;
    QString destination;
public:
    Request(){ }
    Request(QJsonObject obj){
        this->id = obj["id"].toInt();
        this->clientId = obj["client"].toInt();
        this->cargo = obj["cargo"].toString();
        this->weight = obj["weight"].toInt();
        this->departure = obj["departure"].toString();
        this->destination = obj["destination"].toString();
    }
    Request(int id, int clientId, QString cargo, int weight, QString departure, QString destination){
        this->id = id;
        this->clientId = clientId;
        this->cargo = cargo;
        this->weight = weight;
        this->departure = departure;
        this->destination = destination;
    }
    int getId(){ return id; }
    int getClientId(){ return clientId; }
    QString getCargo(){ return cargo; }
    int getWeight(){ return weight; }
    QString getDeparture(){ return departure; }
    QString getDestination(){ return destination; }
    void setId(int id){ this->id = id; }
    void setClientId(int clientId){ this->clientId = clientId; }
    void setCargo(QString cargo){ this->cargo = cargo; }
    void setWeight(int weight){ this->weight = weight; }
    void setDeparture(QString departure){ this->departure = departure; }
    void setDestination(QString destination){ this->destination = destination; }
};

class Order {
private:
    int id;
    int clientId;
    QString cargo;
    int weight;
    QString departure;
    QString destination;
    int passageId;
    int status;
public:
    Order(){ }
    Order(QJsonObject obj){
        this->id = obj["id"].toInt();
        this->clientId = obj["client"].toInt();
        this->cargo = obj["cargo"].toString();
        this->weight = obj["weight"].toInt();
        this->departure = obj["departure"].toString();
        this->destination = obj["destination"].toString();
        this->passageId = obj["passage"].toInt();
        this->status = obj["status"].toInt();
    }
    Order(Request req){
        this->id = req.getId();
        this->clientId = req.getClientId();
        this->cargo = req.getCargo();
        this->weight = req.getWeight();
        this->departure = req.getDeparture();
        this->destination = req.getDestination();
        this->passageId = -1;
        this->status = 0;
    }
    Order(Request req, int passageId){
        this->id = req.getId();
        this->clientId = req.getClientId();
        this->cargo = req.getCargo();
        this->weight = req.getWeight();
        this->departure = req.getDeparture();
        this->destination = req.getDestination();
        this->passageId = passageId;
        this->status = 1;
    }
    int getId(){ return id; }
    int getClientId(){ return clientId; }
    QString getCargo(){ return cargo; }
    int getWeight(){ return weight; }
    QString getDeparture(){ return departure; }
    QString getDestination(){ return destination; }
    int getPassageId(){ return passageId; }
    int getStatus(){ return status; }
    void setId(int id){ this->id = id; }
    void setClientId(int clientId){ this->clientId = clientId; }
    void setCargo(QString cargo){ this->cargo = cargo; }
    void setWeight(int weight){ this->weight = weight; }
    void setDeparture(QString departure){ this->departure = departure; }
    void setDestination(QString destination){ this->destination = destination; }
    void setPassageId(int passageId){ this->passageId = passageId; }
    void setStatus(int status){ this->status = status; }
};

class Passage{
private:
    int id;
    int transportId;
    QString startDate;
    QList <QString> waypoints;
public:
    QList <QString> JArrToLst(QJsonArray arr){
        QList <QString> lst;
        for (const auto &value: arr){
            lst.push_back(value.toString());
        }
        return lst;
    }
    Passage(){ }
    Passage(QJsonObject obj){
        this->id = obj["id"].toInt();
        this->transportId = obj["transport"].toInt();
        this->startDate = obj["start"].toString();
        this->waypoints = JArrToLst(obj["waypoints"].toArray());
    }
    Passage(int id, int transportId, QString startDate){
        this->id = id;
        this->transportId = transportId;
        this->startDate = startDate;
    }
    int getId(){ return id; }
    int getTransportId(){ return transportId; }
    QString getStartDate(){ return startDate; }
    QList <QString> getWaypoints(){ return waypoints; }
    void setId(int id){ this->id = id; }
    void setTransportId(int transportId){ this->transportId = transportId; }
    void setStartDate(QString startDate){ this->startDate = startDate; }
    void setWaypoints(QList <QString> waypoints){ this->waypoints = waypoints; }
    void setStart(QString point){
        if (waypoints.size() > 0){
            waypoints[0] = point;
        } else {
            waypoints.push_front(point);
        }
    }
    void addPoint(QString point){
        waypoints.push_back(point);
    }
    void addPoint(QString point, int index){
        waypoints.insert(index, point);
    }
};

class Transport{
private:
    int id;
    QString type;
    int capacity;
    int status;
    int consumption;
public:
    Transport(){ }
    Transport(QJsonObject obj){
        this->id = obj["id"].toInt();
        this->type = obj["type"].toString();
        this->capacity = obj["capacity"].toInt();
        this->status = obj["status"].toInt();
        this->consumption = obj["consumption"].toInt();
    }
    Transport(int id, QString type, int capacity, int consumption){
        this->id = id;
        this->type = type;
        this->capacity = capacity;
        this->consumption = consumption;
        this->status = 0;
    }
    int getId(){ return id; }
    QString getType(){ return type; }
    int getCapacity(){ return capacity; }
    int getStatus(){ return status; }
    int getConsumption(){ return consumption; }
    void setId(int id){ this->id = id; }
    void setType(QString type){ this->type = type; }
    void setCapacity(int capacity){ this->capacity = capacity; }
    void setStatus(int status){ this->status = status; }
    void setConsumption(int consumption){ this->consumption = consumption; }
};

class Finance{
private:
    int id;
    int orderId;
    int sum;
    QString date;
    int type;
public:
    Finance(){ }
    Finance(QJsonObject obj){
        this->id = obj["id"].toInt();
        this->orderId = obj["order"].toInt();
        this->sum = obj["sum"].toInt();
        this->date = obj["date"].toString();
        this->type = obj["type"].toInt();
    }
    Finance(int id, int orderId, int sum, QString date, int type){
        this->id = id;
        this->orderId = orderId;
        this->sum = sum;
        this->date = date;
        this->type = type;
    }
    int getId(){ return id; }
    int getOrderId(){ return orderId; }
    int getSum(){ return sum; }
    QString getDate(){ return date; }
    int getType(){ return type; }
    void setId(int id){ this->id = id; }
    void setOrderId(int orderId){ this->orderId = orderId; }
    void setSum(int sum){ this->sum = sum; }
    void setType(int type){ this->type = type; }
    void setDate(QString date){ this->date = date; }
    int getValue(){
        return sum * type;
    }
};

// class Array{
// private:
//     QList <Object> array;
// public:
//     template <typename T>
//     QList <T> qSort(QList <T> list, int size, int compare(T, T), int i = 0){
//         int j =  i + size - 1;
//         T mid = list.value(i + size / 2);
//         do {
//             while (compare(list.value(i), mid) == 1){
//                 i++;
//             }
//             while (compare(list.value(j), mid) == 0){
//                 j--;
//             }
//             if (i <= j){
//                 list.swapItemsAt(i, j);
//                 i++;
//                 j--;
//             }
//         } while (i <= j);
//         if (j > 0){
//             list = qSort(list, j + 1, compare);
//         }
//         if (i < size){
//             list = qSort(list, size - i, compare, i);
//         }
//         return list;
//     }
// };

class RequestArray
{
private:
    QList <Request> array;
public:
    RequestArray(){
        QFile file("./files/requests.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray requestArray = doc.object()["requests"].toArray();
        for (const auto &value: requestArray) {
            if (value.isObject()){
                array.push_back(Request(value.toObject()));
            }
        }
    }
    void save(){
        QJsonArray jsonArray;
        QJsonObject obj;
        for(Request req: array){
            QJsonObject currentReq;
            currentReq.insert("id", QJsonValue::fromVariant(req.getId()));
            currentReq.insert("clientId", QJsonValue::fromVariant(req.getClientId()));
            currentReq.insert("cargo", QJsonValue::fromVariant(req.getCargo()));
            currentReq.insert("weight", QJsonValue::fromVariant(req.getWeight()));
            currentReq.insert("departure", QJsonValue::fromVariant(req.getDeparture()));
            currentReq.insert("destination", QJsonValue::fromVariant(req.getDestination()));
            jsonArray.append(currentReq);
        }
        obj.insert("requests", jsonArray);
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QFile file("./files/requests.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << jsonString;
        file.close();
    }
    QList <Request> getArray(){ return array; }
    void setArray(QList <Request> array){ this->array = array; }
    bool isExists(int id){
        for (Request request: array){
            if (request.getId() == id){
                return true;
            }
        }
        return false;
    }
    int getIndex(int id){
        for (int i = 0; i < array.size(); i++){
            if (array.value(i).getId() == id){
                return i;
            }
        }
        return -1;
    }

    // void sort(){
    //     this->array = qSort(this->array, this->array.size(), compareRequestsByWeight);
    // }
    int newId(){
        int id = array.size();
        while (isExists(id)) id++;
        return id;
    }
    Request addRequest(Request request){
        request.setId(newId());
        array.push_back(request);
        return request;
    }
    Request addRequest(int clientId, QString cargo, int weight, QString departure, QString destination){
        Request request(newId(), clientId, cargo, weight, departure, destination);
        array.push_back(request);
        return request;
    }
    Request getRequest(int index){
        return array.value(index);
    }
    Request getRequestById(int id){
        return getRequest(getIndex(id));
    }
    void swap(int index, Request request){
        array.replace(index, request);
    }
    void deleteRequest(int index){
        array.removeAt(index);
    }
};

class OrderArray{
private:
    QList <Order> array;
public:
    OrderArray(){
        QFile file("./files/orders.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray orderArray = doc.object()["orders"].toArray();
        for (const auto &value: orderArray) {
            if (value.isObject()){
                array.push_back(Order(value.toObject()));
            }
        }
    }
    void save(){
        QJsonArray jsonArray;
        QJsonObject obj;
        for(Order ord: array){
            QJsonObject currentOrd;
            currentOrd.insert("id", QJsonValue::fromVariant(ord.getId()));
            currentOrd.insert("clientId", QJsonValue::fromVariant(ord.getClientId()));
            currentOrd.insert("cargo", QJsonValue::fromVariant(ord.getCargo()));
            currentOrd.insert("weight", QJsonValue::fromVariant(ord.getWeight()));
            currentOrd.insert("departure", QJsonValue::fromVariant(ord.getDeparture()));
            currentOrd.insert("destination", QJsonValue::fromVariant(ord.getDestination()));
            currentOrd.insert("passage", QJsonValue::fromVariant(ord.getPassageId()));
            currentOrd.insert("status", QJsonValue::fromVariant(ord.getStatus()));
            jsonArray.append(currentOrd);
        }
        obj.insert("orders", jsonArray);
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QFile file("./files/orders.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << jsonString;
        file.close();
    }
    QList <Order> getArray(){ return array; }
    bool isExists(int id){
        for (Order order: array){
            if (order.getId() == id){
                return true;
            }
        }
        return false;
    }
    int getIndex(int id){
        for (int i = 0; i < array.size(); i++){
            if (array.value(i).getId() == id){
                return i;
            }
        }
        return -1;
    }
    int newId(){
        int id = array.size();
        while (isExists(id)) id++;
        return id;
    }
    Order addOrder(Order order, int passageId){
        order.setId(newId());
        order.setPassageId(passageId);
        array.push_back(order);
        return order;
    }
    // void addOrder(int clientId, QString cargo, int weight, QString departure, QString destination, int passageId){
    //     array.push_back(Order(newId(), clientId, cargo, weight, departure, destination, passageId));
    // }
    Order getOrder(int index){
        return array.value(index);
    }
    Order getOrderById(int id){
        return getOrder(getIndex(id));
    }
    void swap(int index, Order order){
        array.replace(index, order);
    }
    void deleteOrder(int index){
        array.removeAt(index);
    }
    Order requestToOrder(Request request){
        return Order(request);
    }
    Order addOrderByRequest(Request request, int passageId){
        Order order = requestToOrder(request);
        addOrder(order, passageId);
        order.setPassageId(passageId);
        return order;
    }
};


class PassageArray{
private:
    QList <Passage> array;
public:
    PassageArray(){
        QFile file("./files/passages.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray passageArray = doc.object()["passages"].toArray();
        for (const auto &value: passageArray) {
            if (value.isObject()){
                array.push_back(Passage(value.toObject()));
            }
        }
    }
    void save(){
        QJsonArray jsonArray;
        QJsonObject obj;
        for(Passage pass: array){
            QJsonObject currentPass;
            currentPass.insert("id", QJsonValue::fromVariant(pass.getId()));
            currentPass.insert("transport", QJsonValue::fromVariant(pass.getTransportId()));
            currentPass.insert("date", QJsonValue::fromVariant(pass.getStartDate()));
            currentPass.insert("waypoints", QJsonValue::fromVariant(pass.getWaypoints()));
            jsonArray.append(currentPass);
        }
        obj.insert("passages", jsonArray);
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QFile file("./files/passages.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << jsonString;
        file.close();
    }
    QList <Passage> getArray(){ return array; }
    bool isExists(int id){
        for (Passage passage: array){
            if (passage.getId() == id){
                return true;
            }
        }
        return false;
    }
    int getIndex(int id){
        for (int i = 0; i < array.size(); i++){
            if (array.value(i).getId() == id){
                return i;
            }
        }
        return -1;
    }
    int newId(){
        int id = array.size();
        while (isExists(id)) id++;
        return id;
    }
    Passage addPassage(Passage passage, int transportId){
        passage.setId(newId());
        passage.setTransportId(transportId);
        array.push_back(passage);
        return passage;
    }
    Passage addPassage(int transportId, QString date){
        Passage passage(newId(), transportId, date);
        array.push_back(passage);
        return passage;
    }
    Passage getPassage(int index){
        return array.value(index);
    }
    Passage getPassageById(int id){
        return getPassage(getIndex(id));
    }
    void swap(int index, Passage passage){
        array.replace(index, passage);
    }
    void deletePassage(int index){
        array.removeAt(index);
    }
};

class TransportArray{
private:
    QList <Transport> array;
public:
    TransportArray(){
        QFile file("./files/transports.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray transportArray = doc.object()["transports"].toArray();
        for (const auto &value: transportArray) {
            if (value.isObject()){
                array.push_back(Transport(value.toObject()));
            }
        }
    }
    void save(){
        QJsonArray jsonArray;
        QJsonObject obj;
        for(Transport trans: array){
            QJsonObject currentTrans;
            currentTrans.insert("id", QJsonValue::fromVariant(trans.getId()));
            currentTrans.insert("type", QJsonValue::fromVariant(trans.getType()));
            currentTrans.insert("capacity", QJsonValue::fromVariant(trans.getCapacity()));
            currentTrans.insert("consumption", QJsonValue::fromVariant(trans.getConsumption()));
            currentTrans.insert("status", QJsonValue::fromVariant(trans.getStatus()));
            jsonArray.append(currentTrans);
        }
        obj.insert("transports", jsonArray);
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QFile file("./files/transports.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << jsonString;
        file.close();
    }
    QList <Transport> getArray(){ return array; }
    bool isExists(int id){
        for (Transport transport: array){
            if (transport.getId() == id){
                return true;
            }
        }
        return false;
    }
    int getIndex(int id){
        for (int i = 0; i < array.size(); i++){
            if (array.value(i).getId() == id){
                return i;
            }
        }
        return -1;
    }
    int newId(){
        int id = array.size();
        while (isExists(id)) id++;
        return id;
    }
    Transport addTransport(Transport transport){
        transport.setId(newId());
        array.push_back(transport);
        return transport;
    }
    Transport addTransport(QString type, int capacity, int consumption){
        Transport transport(newId(), type, capacity, consumption);
        array.push_back(transport);
        return transport;
    }
    Transport getTransport(int index){
        return array.value(index);
    }
    Transport getTransportById(int id){
        return getTransport(getIndex(id));
    }
    void swap(int index, Transport transport){
        array.replace(index, transport);
    }
    void deleteTransport(int index){
        array.removeAt(index);
    }
};


class FinanceArray{
private:
    QList <Finance> array;
public:
    FinanceArray(){
        QFile file("./files/finances.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonArray financeArray = doc.object()["finances"].toArray();
        for (const auto &value: financeArray) {
            if (value.isObject()){
                array.push_back(Finance(value.toObject()));
            }
        }
    }
    void save(){
        QJsonArray jsonArray;
        QJsonObject obj;
        for(Finance fin: array){
            QJsonObject currentFin;
            currentFin.insert("id", QJsonValue::fromVariant(fin.getId()));
            currentFin.insert("order", QJsonValue::fromVariant(fin.getOrderId()));
            currentFin.insert("sum", QJsonValue::fromVariant(fin.getSum()));
            currentFin.insert("date", QJsonValue::fromVariant(fin.getDate()));
            currentFin.insert("type", QJsonValue::fromVariant(fin.getType()));
            jsonArray.append(currentFin);
        }
        obj.insert("finances", jsonArray);
        QJsonDocument doc(obj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QFile file("./files/finances.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << jsonString;
        file.close();
    }
    QList <Finance> getArray(){ return array; }
    bool isExists(int id){
        for (Finance finance: array){
            if (finance.getId() == id){
                return true;
            }
        }
        return false;
    }
    int getIndex(int id){
        for (int i = 0; i < array.size(); i++){
            if (array.value(i).getId() == id){
                return i;
            }
        }
        return -1;
    }
    int newId(){
        int id = array.size();
        while (isExists(id)) id++;
        return id;
    }
    Finance addFinance(Finance finance){
        finance.setId(newId());
        array.push_back(finance);
        return finance;
    }
    Finance addFinance(int orderId, int sum, QString date, int type){
        Finance finance(newId(), orderId, sum, date, type);
        array.push_back(finance);
        return finance;
    }
    Finance getFinance(int index){
        return array.value(index);
    }
    Finance getFinanceById(int id){
        return getFinance(getIndex(id));
    }
    void swap(int index, Finance finance){
        array.replace(index, finance);
    }
    void deleteFinance(int index){
        array.removeAt(index);
    }
};

class Files{
public:
    RequestArray requests;
    OrderArray orders;
    PassageArray passages;
    TransportArray transports;
    FinanceArray finances;
    void save(){
        requests.save();
        orders.save();
        passages.save();
        transports.save();
        finances.save();
    }
};


#endif // CLASSES_H
