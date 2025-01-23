#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
enum TypeOFButton{
    BUTTON_TIME = 0,
    BUTTON_TEXT
};

#define BIND_PORT 12345

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data );

    void ReadDatagramText(QNetworkDatagram datagram);
    void SendDatagramText(QByteArray data );
    QString GetSendlerAddr();
    QString GetSendlerPort();

private slots:
    void readPendingDatagrams(void);

public slots:
    void setTypeOfButton( TypeOFButton);
private:
    QUdpSocket* serviceUdpSocket;
    TypeOFButton BUTTON;
    QString SendlerAddr;
    QString SendlerPort;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTextToGUI(QString data);

};

#endif // UDPWORKER_H
