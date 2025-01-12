#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_buttons_->setObjectName("groupBox_buttons");
    ui->groupBox_buttons_->setStyleSheet("#groupBox_buttons{border:0}");
    ui->groupBox_time_and_circle->setObjectName("groupBox_time_and_circle");
    ui->groupBox_time_and_circle->setStyleSheet("#groupBox_time_and_circle{border:0}");
    ui->pushButton_circle_->setStyleSheet("QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->pushButton_clear_->setStyleSheet("QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->pushButton_start_stop_->setStyleSheet("QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->pushButton_circle_->setEnabled(false);
    stopwatch_ = new StopWatch(this);
    ui->label_status_->setStyleSheet("QLabel { color : red; }");
    connect( stopwatch_, &StopWatch::sendTimeoutSig,this, &MainWindow::acceptTime);

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_start_stop__clicked()
{
    if(Start){
        ui->pushButton_start_stop_->setText("Стоп");
        ui->pushButton_circle_->setEnabled(true);
        Start = false;
        stopwatch_->setTimeTimer(100);
        ui->label_status_->setStyleSheet("QLabel { color : green; }");
        ui->label_status_ ->setText("Включен");

    }else{
        ui->pushButton_start_stop_->setText("Старт");
        Start = true;
        ui->pushButton_circle_->setEnabled(false);
        stopwatch_->stopTimer();
        ui->label_status_->setStyleSheet("QLabel { color : red; }");
        ui->label_status_ ->setText("Отключен");

    }
}
void MainWindow::acceptTime()
{
    stopwatch_->incrementTimer();
    QString str = QString::number(stopwatch_->getTimeTimer());
    ui->label_time_text_->setText(str);
}


void MainWindow::on_pushButton_clear__clicked()
{
    stopwatch_->refreshTimer();
    ui->label_time_text_->setText("0");
    ui->textBrowser_time_circle_->clear();
    number_of_circle_ = 0;
}


void MainWindow::on_pushButton_circle__clicked()
{
    ++number_of_circle_;
    double time = stopwatch_->getTimeTimer();

    if(number_of_circle_ == 1)
    {
        ui->textBrowser_time_circle_->append(QString("Круг № %1 Время: %2").arg(number_of_circle_).arg(time,1,'f',1));
        time_circle_ = time;
    }else
    {
        double new_time = time-time_circle_;
        ui->textBrowser_time_circle_->append(QString("Круг № %1 Время: %2").arg(number_of_circle_).arg(new_time,1,'f',1));

        time_circle_ = time;
    }
}

