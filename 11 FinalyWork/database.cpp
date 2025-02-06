#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();

}

DataBase::~DataBase()
{
    delete dataBase;
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


