#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendTextToGUI, this, &MainWindow::DisplayText);
    connect(this, &MainWindow::sig_SendTypeOFButton, udpWorker,&UDPworker::setTypeOfButton);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        //timer->start(TIMER_DELAY); излишнее

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{   emit sig_SendTypeOFButton(TypeOFButton::BUTTON_TIME);
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));


}

void MainWindow::DisplayText(QString data)
{
    counterTxT++;
    if(counterTxT % 20 == 0){
        ui->te_result->clear();
    }

    int size = data.toLocal8Bit().size();
    QString Addr = udpWorker->GetSendlerAddr();
    QString Port = udpWorker->GetSendlerPort();
    ui->te_result->append( "№" + QString::number(counterTxT));
    ui->te_result->append("Msg: " + data + ". "
      " " + "байты: "
      + QString::number(size)+ " отправитель: " + Addr+":"+Port);


}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();

}




void MainWindow::on_pb_send_data__clicked()

{   QString str = ui->te_data_->text();
    emit sig_SendTypeOFButton(TypeOFButton::BUTTON_TEXT);
    QByteArray dataToSend;
    QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
    outStr << str;
    udpWorker->SendDatagram(dataToSend);

}

