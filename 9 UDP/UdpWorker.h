#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>

#define BIND_PORT 12345
enum Message{
    TIME = 0,
    TEXT
};

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data, Message message);

    void ReadDatagramText(QNetworkDatagram datagram);
    void SendDatagramText(QByteArray data );
    QString GetSendlerAddr();
    QString GetSendlerPort();

private slots:
    void readPendingDatagrams(void);
    void readPendingDatagramsText(void);
public slots:
private:
    QUdpSocket* serviceUdpSocket;
    QUdpSocket *serviceUdpSocketMessage;
    QString SendlerAddr;
    QString SendlerPort;
    Message message_;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTextToGUI(QString data);

};

#endif // UDPWORKER_H
