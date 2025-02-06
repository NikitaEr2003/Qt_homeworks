#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "database.h"
#include <QMessageBox>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_connect__clicked();
    void slot_status_connection(bool);
    void slot_refresh_connection();
    void on_pushButton_clear__clicked();

private:
    void myConnect();
    bool connectionStatus = false;;
    Ui::MainWindow *ui;
    DataBase* myDataBase;
    QMessageBox* msg;
    QVector<QString> dataForConnect;
    QTimer * timer;
};
#endif // MAINWINDOW_H
