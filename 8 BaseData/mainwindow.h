#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void ReceiveStatusConnectionToDB(bool status);


private slots:
    void on_button_clear__clicked();

    void on_button_connect__clicked();

    void on_button_request__clicked();

    void on_button_exit__clicked();

    void on_button_clear_request__clicked();

    void on_checkBox_full_table__checkStateChanged(const Qt::CheckState &arg1);

signals:
    void sig_RequestToDb(QString request);

    void sig_SendFull(bool);


private:
    void AcceptDataFromText();

    ClearTableView TypeOfClear;

    QVector<QString> dataForConnect; //Данные для подключения к БД.

    Ui::MainWindow *ui;
    DataBase* dataBase;
    QMessageBox* msg;

};
#endif // MAINWINDOW_H
