#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>


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

    void AddDataBase(QString driver, QString nameDB = "");
    void DisconnectFromDataBase(QString nameDb = "");
    QSqlError GetLastError(void);
    void ConnectToDataBase(QVector<QString> dataForConnect);
    QSqlTableModel * GetModelTable() const;
    QSqlQueryModel * GetModelQuery() const;
    ClearTableView GetModelType() const;


signals:
    void sig_SendDataReady(QVector<QString> dataForConnect);
    void sig_SendStatusConnection(bool);
    void sig_SendModelRequest();

private slots:
    void slot_SendModelRequest();

public slots:
    void slot_RequestToDB(QString request);
    void slot_ChangeCheckFull(bool);


private:
    bool checkFullTable = true;
    QSqlDatabase* dataBase;
    QSqlTableModel * modelTable = nullptr;
    QSqlQueryModel * modelQuery = nullptr;
    QString request;
    ClearTableView TypeOfTabe = ClearTableView::NOTHING;

};

#endif // DATABASE_H
