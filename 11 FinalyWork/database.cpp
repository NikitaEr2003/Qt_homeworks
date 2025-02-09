#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    modelQueryAirports = new QSqlQueryModel(this);
    modelQueryFlights = new QSqlQueryModel(this);


}

DataBase::~DataBase()
{
    delete dataBase;
    delete query;
}

void DataBase::addDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

void DataBase::connectToDataBase(QVector<QString> data)
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
    query = new QSqlQuery(*dataBase);
}

QSqlQueryModel * DataBase::getAirportsRequests(QString str, bool flag){

    query->exec(str);
    if(flag){
    modelQueryAirports->setQuery((*query));
    if (modelQueryAirports->lastError().isValid()) {
        qDebug() << "Ошибка в запросе: " << modelQueryAirports->lastError().text();
    } else
    {
        qDebug() << "Запрос выполнен успешно";

    }
    int size = modelQueryAirports->rowCount();
    while(size--){
    QSqlRecord record = modelQueryAirports->record(size); // Получаем первую запись из модели
    QVariant NameCity;
    QVariant Code;

    for (int i = 0; i < record.count(); ++i) {
        if(i == 0){
           NameCity = record.value(i);
        }
        else
        {
           Code = record.value(i);
        }
    }
    mapCityAndCode.insert(NameCity.toString(),Code.toString());

    }
    return modelQueryAirports;
    }
    else
    {
        modelQueryFlights->setQuery((*query));
        if (modelQueryFlights->lastError().isValid()) {
            qDebug() << "Ошибка в запросе: " << modelQueryFlights->lastError().text();
        } else {
            qDebug() << "Запрос выполнен успешно";

        }
    return modelQueryFlights;
    }





}

void DataBase::disconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}

QSqlError DataBase::getLastError()
{
    return dataBase->lastError();
}


bool DataBase::isOpen(){
    return dataBase->isOpen();
}


