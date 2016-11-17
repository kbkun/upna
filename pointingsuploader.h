#ifndef POINTINGSUPLOADER_H
#define POINTINGSUPLOADER_H

#include <QSharedPointer>
#include <QSerialPort>
#include <QTimer>
#include <QQueue>
#include "convertation.h"
#include "kama.pb.h"

struct PointsFrame {
    quint16 azimuth;
    quint16 elevation;
};

class PointingsUploader : public QObject
{
    Q_OBJECT
public:
    virtual ~PointingsUploader() = 0;
    virtual void upload(const kama::protocol::PointingTable&, QSerialPort* serial) = 0;
public slots:
    virtual void start() = 0;
signals:
//    void pt_upload(const PointingTab&);
};

class RealPointingsUploader : public PointingsUploader
{
    Q_OBJECT
    bool isUpl;
    QTimer* timer;
    QQueue<PointsFrame> frameQueue;
    QSerialPort *serial;
public:
    RealPointingsUploader();
    bool isUploading() { return isUpl; }
    void upload(const kama::protocol::PointingTable& pt, QSerialPort* s);
public slots:
    void start();
private slots:
    void timerOverflow();
};

class DummyPointingsUploader : public PointingsUploader
{
    Q_OBJECT
public:
    void upload(const kama::protocol::PointingTable&, QSerialPort* serial);
public slots:
    void start() {;}
signals:
//    void pt_upload(const PointingTab&);
};

QSharedPointer<PointingsUploader> createRealUploader();
QSharedPointer<PointingsUploader> createDummyUploader();

#endif // POINTINGSUPLOADER_H
