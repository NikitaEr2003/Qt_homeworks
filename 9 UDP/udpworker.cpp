#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    serviceUdpSocketMessage = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
     serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);
     serviceUdpSocketMessage->bind(QHostAddress::LocalHost, 1234);
     connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);
     connect(serviceUdpSocketMessage, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagramsText);



}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{

    QByteArray data;
    data = datagram.data();
    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;
    inStr >> dateTime;

    emit sig_sendTimeToGUI(dateTime);
}

void UDPworker::ReadDatagramText(QNetworkDatagram datagram){
    QByteArray data;
    data = datagram.data();
    QHostAddress addresSendler = datagram.senderAddress();
    SendlerAddr = addresSendler.toString();

     int port = datagram.senderPort();
    SendlerPort = QString::number(port);

    QDataStream inStr(&data, QIODevice::ReadOnly);
    QString dateStr;
    inStr >> dateStr;
    emit sig_sendTextToGUI(dateStr);

}
/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data, Message message)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    if(message == Message::TIME){
        serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
    }
    else if(message == Message::TEXT)
    {
        serviceUdpSocketMessage->writeDatagram(data, QHostAddress::LocalHost, 1234);
    }

}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
                ReadDatagram(datagram);

    }

}

void UDPworker::readPendingDatagramsText( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocketMessage->hasPendingDatagrams()){
        QNetworkDatagram datagram = serviceUdpSocketMessage->receiveDatagram();
        ReadDatagramText(datagram);
    }

}


QString UDPworker::GetSendlerAddr(){
    return SendlerAddr;
}

QString UDPworker::GetSendlerPort(){
    return SendlerPort;
}
