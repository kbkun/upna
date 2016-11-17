#include "pointingsuploader.h"
#include <cmath>
#include <iostream>
#include "crc.h"

PointingsUploader::~PointingsUploader()
{

}

RealPointingsUploader::RealPointingsUploader()
    : isUpl(false)
    , timer(new QTimer(this))
{

}

void RealPointingsUploader::upload(const kama::protocol::PointingTable& pt, QSerialPort *s)
{
    serial = s;
    google::protobuf::RepeatedPtrField<kama::protocol::PointingTableItem>::const_iterator it = pt.item().begin();
    for(; it < pt.item().end(); ++it) {
        PointsFrame tmpFrame;
        kama::protocol::PointingTableItem item = *it;
        quint16 az = static_cast<quint16>(item.azimuth() / 0.010986328125);
        az &= 077777;   // в азимуте 15 разрядов
        quint16 el = static_cast<quint16>(abs(item.elevation()) / 0.010986328125);
        el &= 037777;   // в УМ 14 разрядов
        tmpFrame.azimuth = az;
        tmpFrame.elevation = el;
        frameQueue.append(tmpFrame);
    }
}

void RealPointingsUploader::timerOverflow()
{
    if(frameQueue.isEmpty()) {
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(timerOverflow()));
    }
    else {
        PointsFrame tmpFrame = frameQueue.dequeue();
        QByteArray tmpArr;
        tmpArr.append(0353);                                //МНС                           0
        tmpArr.append(1);                                   //номер РЛС "Кама-Н"            1
        tmpArr.append(1);                                   //признак режима ЦУ             2
        tmpArr.append((tmpFrame.azimuth & 040000) >> 14);   //14-й разряд азимута           3
        tmpArr.append((tmpFrame.azimuth & 037600) >> 7);    //7...13 разряды азимута        4
        tmpArr.append(tmpFrame.azimuth & 0177);             //0...6 разряды азимута         5
        tmpArr.append((tmpFrame.elevation & 037600) >> 7);  //7...13 разряды УМ             6
        tmpArr.append(tmpFrame.elevation & 0177);           //0...6 разряды УМ              7
        tmpArr.append(0234);                                //МКС                           8
        tmpArr.append(kama::crc(reinterpret_cast<unsigned char*>(tmpArr.data()), tmpArr.length()));
        serial->write(tmpArr);
    }
}

void RealPointingsUploader::start()
{
    qDebug() << "void RealPointingsUploader::start()";
    connect(timer, SIGNAL(timeout()), SLOT(timerOverflow()));
    timerOverflow();
    timer->start(50);
}

QSharedPointer<PointingsUploader> createRealUploader()
{
    return QSharedPointer<PointingsUploader>(new RealPointingsUploader);
}

void DummyPointingsUploader::upload(const kama::protocol::PointingTable &pt, QSerialPort *serial)
{
//    emit pt_upload(pt);
}

QSharedPointer<PointingsUploader> createDummyUploader()
{
    return QSharedPointer<PointingsUploader>(new DummyPointingsUploader);
}
