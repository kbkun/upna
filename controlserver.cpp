#include "controlserver.h"

ControlServer::ControlServer()
{
    state.registrationDeviceConnected =  false;
    state.pointingDeviceConnected = false;
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
}

ControlServer::~ControlServer()
{
  stop();
}

bool ControlServer::start(const QHostAddress& addr, qint16 port)
{
  return m_tcpServer.listen(addr, port);
}

void ControlServer::stop()
{
    m_tcpServer.close();
    qDeleteAll(m_clients);
}

void ControlServer::publish(const Frame& f)
{
    Q_FOREACH(QTcpSocket* client, m_clients)
      {
        kama::protocol::Envelope msg;
        msg.mutable_angle_channel_state()->set_time_mode(f.timeMode);
        msg.mutable_angle_channel_state()->set_time(f.time.toString("yyyy-MM-ddThh:mm:ss.zzz").toStdString());
        msg.mutable_angle_channel_state()->set_tracking_mode(f.trackingMode);
        msg.mutable_angle_channel_state()->set_azimuth(f.azimuth);
        msg.mutable_angle_channel_state()->set_elevation(f.elevation);
        client->write(serializeDelimited(msg));
      }
}

void ControlServer::handleNewConnection()
{
    while (m_tcpServer.hasPendingConnections())
    {
        QTcpSocket* client = m_tcpServer.nextPendingConnection();
        new ClientBuffer(client);
        connect(client, SIGNAL(readyRead()), this, SLOT(clientReadyRead()));
        connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        m_clients.append(client);
        Q_EMIT clientCountChanged(m_clients.size());
    }
}

void ControlServer::clientReadyRead()
{
    if (QTcpSocket* client = qobject_cast<QTcpSocket *>(sender()))
    {
        const QByteArray& data = client->readAll();

        ClientBuffer* buffer = client->findChild<ClientBuffer*>(QString("ClientBuffer"));
        buffer->m_buffer += data;

        for (;;)
        {
            size_t bytesConsumed = 0;
            const QSharedPointer<kama::protocol::Envelope>& msg =
                    parseDelimited<kama::protocol::Envelope>(buffer->m_buffer.constData(),
                                                             buffer->m_buffer.size(),
                                                             bytesConsumed);

           if (bytesConsumed > 0) {
                 buffer->m_buffer.remove(0, bytesConsumed);
            }

            if (msg) {
                processMessage(*msg, client);
            } else {
                break;
            }
        }
    }
}

void ControlServer::clientDisconnected()
{
    if (QTcpSocket* client = qobject_cast<QTcpSocket *>(sender()))
    {
        m_clients.removeAll(client);
        client->deleteLater();
        Q_EMIT clientCountChanged(m_clients.size());
    }
}

void ControlServer::processMessage(const kama::protocol::Envelope& msg, QTcpSocket* client, bool ack)
{
//    qDebug() << QString::fromStdString(msg.Utf8DebugString());
    if (msg.has_pointing_table_setting_req()) processMessage(msg.pointing_table_setting_req(), client, ack);
    else if (msg.has_pointing_table_getting_req()) processMessage(msg.pointing_table_getting_req(), client);
    else if (msg.has_calibration_table_setting_req()) processMessage(msg.calibration_table_setting_req(), client);
    else if (msg.has_calibration_table_getting_req()) processMessage(msg.calibration_table_getting_req(), client);
    else if (msg.has_state_getting_req()) processMessage(msg.state_getting_req(), client);
    else qDebug() << "Неизвестное мне сообщение пришло";
}

void ControlServer::processMessage(const kama::protocol::PointingTableSettingReq& msg, QTcpSocket *client, bool ack)
{
    errString.clear();
    mPT.CopyFrom(msg.table());
    if(check()) {
        slice();
        if(ack) {
            kama::protocol::Envelope reply;
            reply.mutable_pointing_table_setting_ack();
            client->write(serializeDelimited(reply));
//            qDebug() << QString::fromStdString(reply.Utf8DebugString());
        }
        emit pTableIsValid();
    } else {
        if(ack) {
            kama::protocol::Envelope reply;
            reply.mutable_pointing_table_setting_nak()->set_error_message(errString.toStdString());
            client->write(serializeDelimited(reply));
        }
        emit pTableIsNotValid();
    }
}

void ControlServer::processMessage(const kama::protocol::PointingTableGettingReq& msg, QTcpSocket *client)
{
    kama::protocol::Envelope reply;
    qDebug() << "отправляю текущую таблицу ЦУ:";
    reply.mutable_pointing_table_getting_ack()->mutable_table()->CopyFrom(mPT);
    client->write(serializeDelimited(reply));
}

void ControlServer::processMessage(const kama::protocol::CalibrationTableSettingReq& msg, QTcpSocket *client)
{
    mCT.CopyFrom(msg.table());
    kama::protocol::Envelope reply;
    reply.mutable_calibration_table_setting_ack();
    client->write(serializeDelimited(reply));
    qDebug() << QString::fromStdString(reply.Utf8DebugString());
}

void ControlServer::processMessage(const kama::protocol::CalibrationTableGettingReq& msg, QTcpSocket *client)
{
    kama::protocol::Envelope reply;
    reply.mutable_calibration_table_getting_ack()->CopyFrom(mCT);
    client->write(serializeDelimited(reply));
}

void ControlServer::processMessage(const kama::protocol::StateGettingReq& msg, QTcpSocket *client)
{
    State s = getState();
    kama::protocol::Envelope reply;
    reply.mutable_state_getting_ack()->set_registration_device_connected(s.registrationDeviceConnected);
    reply.mutable_state_getting_ack()->set_pointing_device_connected(s.pointingDeviceConnected);
    client->write(serializeDelimited(reply));
//    qDebug() << QString::fromStdString(reply.Utf8DebugString());
}

bool ControlServer::check()
{
    bool isVal = true;
    google::protobuf::RepeatedPtrField<kama::protocol::PointingTableItem>::const_iterator it = mPT.item().begin();
    ++it;
    if (it == mPT.item().end())
        return isVal;
    for(; it != mPT.item().end(); ++it) {
        kama::protocol::PointingTableItem curItem = *it;
        kama::protocol::PointingTableItem preItem = *(it-1);
        double deltaT = curItem.time() - preItem.time();
        double deltaA = curItem.azimuth() - preItem.azimuth();
        double deltaE = curItem.elevation() - preItem.elevation();
        double dadt = deltaA / deltaT;
        double dedt = deltaE / deltaT;
        if(abs(dadt) > 18) {
            isVal = false;
            QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) скорость движения по азимуту превышает 18 град/с\n",
                                            curItem.time(), curItem.azimuth(), curItem.elevation());
            errString.append(err);
        }
        if(abs(dedt) > 9) {
            isVal = false;
            QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) скорость движения по углу места превышает 9 град/с\n",
                                            curItem.time(), curItem.azimuth(), curItem.elevation());
            errString.append(err);
        }
        if(curItem.elevation() < 2 && dedt < -2) {
            isVal = false;
            QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) движение на нижний упор с недопустимой скоростью\n",
                                            curItem.time(), curItem.azimuth(), curItem.elevation());
            errString.append(err);
        }
        if(curItem.elevation() > 86.5 && dedt > 2) {
            isVal = false;
            QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) движение на верхний упор с недопустимой скоростью\n",
                                            curItem.time(), curItem.azimuth(), curItem.elevation());
            errString.append(err);
        }
    }
    return isVal;
}

void ControlServer::slice()
{
    const int freq = 20;
    google::protobuf::RepeatedPtrField<kama::protocol::PointingTableItem>::const_iterator it = mPT.item().begin();
    ++it;

    if(it == mPT.item().end())
        return;
    kama::protocol::PointingTableItem curItem;
    kama::protocol::PointingTableItem preItem;
    for(; it != mPT.item().end(); ++it) {
        curItem = *it;
        preItem = *(it-1);
        double dt = curItem.time() - preItem.time();
        int ticks = freq * dt;
        double timeInr = (curItem.time() - preItem.time()) / ticks;
        double azIncr = (curItem.azimuth() - preItem.azimuth()) / ticks;
        double elIncr = (curItem.elevation() - preItem.elevation()) / ticks;
        for(int i = 0; i < ticks; ++i) {
            kama::protocol::PointingTableItem *item = slicedPT.mutable_item()->Add();
            double time = preItem.time() + timeInr * i;
            double az = preItem.azimuth() + azIncr * i;
            double el = preItem.elevation() +  elIncr * i;
            item->set_time(time);
            item->set_azimuth(az);
            item->set_elevation(el);
        }
    }
    kama::protocol::PointingTableItem *i = slicedPT.add_item();
    i->set_time(curItem.time());
    i->set_azimuth(curItem.azimuth());
    i->set_elevation(curItem.elevation());
//    qDebug() << QString::fromStdString(slicedPT.Utf8DebugString());
}
