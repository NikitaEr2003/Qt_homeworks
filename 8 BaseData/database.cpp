#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    connect(this, &DataBase::sig_SendModelRequest, this, &DataBase::slot_SendModelRequest);

}

DataBase::~DataBase()
{
    delete dataBase;

    if(modelTable)
    {
        delete modelTable;
    };

    if(modelQuery){
        delete modelQuery;
    }
}

void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

void DataBase::ConnectToDataBase(QVector<QString> data)
{
    dataBase->setHostName(data[HOST_NAME_]);
    dataBase->setDatabaseName(data[DBNAME_]);
    dataBase->setUserName(data[LOGIN_]);
    dataBase->setPassword(data[PASS_]);
    dataBase->setPort(data[PORT_].toInt());

    bool status = dataBase->open();

    if (!status) {
        qDebug() << "Не удалось подключиться к базе данных!";
        emit sig_SendStatusConnection(false);
        return;
    }

    emit sig_SendStatusConnection(true);
}


void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}

void DataBase::slot_RequestToDB(QString request_)
{

    request = request_;

}


QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}

QSqlTableModel * DataBase::GetModelTable() const{
    return  modelTable;
}

QSqlQueryModel * DataBase::GetModelQuery() const{
    return modelQuery;
}


void DataBase::slot_ChangeCheckFull(bool full){
    checkFullTable = full;
    emit sig_SendModelRequest();
}
void DataBase::slot_SendModelRequest(){
    if(checkFullTable){
        if ( modelTable) {
            delete  modelTable;
            modelTable = nullptr;
        }

        modelTable = new QSqlTableModel(nullptr, *dataBase);
        modelTable->setTable("film");
        modelTable->select();
        TypeOfTabe =  ClearTableView::FullTable;
    }
    else{
        if(modelQuery){
            delete modelQuery;
            modelQuery = nullptr;
        }
        modelQuery = new QSqlQueryModel;
        QSqlQuery query(*dataBase);
        query.exec(request);
        modelQuery->setQuery(std::move(query));
        if (modelQuery->lastError().isValid()) {
            qDebug() << "Ошибка в запросе: " << modelQuery->lastError().text();
        } else {
            qDebug() << "Запрос выполнен успешно";
        }
        TypeOfTabe = ClearTableView::Request;
    }

}

ClearTableView DataBase::GetModelType() const {

    return TypeOfTabe;

}
