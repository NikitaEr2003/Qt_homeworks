#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMap>
#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{
    HOST_NAME_ = 0,
    DBNAME_ = 1,
    LOGIN_ = 2,
    PASS_ = 3,
    PORT_ = 4
};

enum ClearTableView{
    FullTable = 0,
    Request,
    NOTHING
};


class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void addDataBase(QString driver, QString nameDB = "");
    void disconnectFromDataBase(QString nameDb = "");
    QSqlError getLastError(void);
    void connectToDataBase(QVector<QString> dataForConnect);;
    bool isOpen();
    QSqlQueryModel * getAirportsRequests(QString str, bool flag);
    QMap<QString, QString>  mapCityAndCode;


signals:
    void sig_SendDataReady(QVector<QString> dataForConnect);
    void sig_SendStatusConnection(bool);

private:
    QSqlQuery*query;
    QSqlDatabase * dataBase;
    QSqlQueryModel * modelQueryAirports = nullptr;
    QSqlQueryModel * modelQueryFlights = nullptr;

};

#endif // DATABASE_H
