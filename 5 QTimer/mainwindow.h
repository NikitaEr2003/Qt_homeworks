#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"
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
    void sendStartTime();

private slots:

    void on_pushButton_start_stop__clicked();

    void acceptTime();

    void on_pushButton_clear__clicked();

    void on_pushButton_circle__clicked();

signals:


private:
    StopWatch * stopwatch_;
    Ui::MainWindow *ui;
    bool Start = true;
    int number_of_circle_ = 0;
    double time_circle_ = 0;

};
#endif // MAINWINDOW_H
