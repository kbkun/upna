#ifndef CONTROLSERVER_H
#define CONTROLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "frame.h"
#include "kama.pb.h"
#include "helpers.h"

struct State
{
    volatile bool registrationDeviceConnected;
    volatile bool pointingDeviceConnected;
};

class ClientBuffer : public QObject
{
    Q_OBJECT
public:
    ClientBuffer(QObject* parent) : QObject(parent), blockSize(0) { this->setObjectName("ClientBuffer"); }
    quint16         blockSize;
    QByteArray      m_buffer;
};

class ControlServer : public QObject
{
  Q_OBJECT
    QTcpServer m_tcpServer;
    QList<QTcpSocket*> m_clients;
    State state;
    kama::protocol::PointingTable mPT;
    kama::protocol::PointingTable slicedPT;
    kama::protocol::CalibrationTable mCT;
    QString errString;
    void processMessage(const kama::protocol::PointingTableSettingReq& msg, QTcpSocket *client, bool ack = true);
    void processMessage(const kama::protocol::PointingTableGettingReq& msg, QTcpSocket *client);
    void processMessage(const kama::protocol::CalibrationTableSettingReq& msg, QTcpSocket *client);
    void processMessage(const kama::protocol::CalibrationTableGettingReq& msg, QTcpSocket *client);
    void processMessage(const kama::protocol::StateGettingReq& msg, QTcpSocket *client);
    bool check();
    void slice();

public:
    explicit ControlServer();
    ~ControlServer();
    void processMessage(const kama::protocol::Envelope& msg, QTcpSocket *client, bool ack = true);

    bool start(const QHostAddress& addr, qint16 port);
    void stop();
    const kama::protocol::PointingTable& getPT() { return mPT; }
    const kama::protocol::PointingTable& getSlicedPT() { return slicedPT; }
    void clearPT() { mPT.Clear(); slicedPT.Clear();}
    const kama::protocol::CalibrationTable& getCT() { return mCT; }
    const State& getState() { return state; }
    bool isListening() { return m_tcpServer.isListening(); }
    QString error() { return errString; }

signals:
    void clientCountChanged(int count);
    void disconnected();
    void pTableIsValid();
    void pTableIsNotValid();

public slots:
    void publish(const Frame& f);
    void registrationDeviceStateChanged(bool s) { state.registrationDeviceConnected = s; }
    void pointingDeviceStateChanged(bool s)     { state.pointingDeviceConnected = s; }

private slots:
    void handleNewConnection();
    void clientReadyRead();
    void clientDisconnected();
};

#endif // CONTROLSERVER_H
