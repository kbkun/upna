#ifndef FRAMEHANDLER_H_
#define FRAMEHANDLER_H_

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QSharedPointer>
#include <QQueue>
#include <stdint.h>
#include <cmath>

#include "frame.h"
#include "pointingtable.h"
#include "kama.pb.h"
#include "helpers.h"

struct FrameHandler : public QObject
{
        Q_OBJECT
public:
    virtual ~FrameHandler() = 0;
    Frame frame;
public slots:
    virtual void receiveChar(unsigned char ch) = 0;
    virtual void receiveTable(PointingTab pt) = 0;
signals:
    void readyToSend(Frame);
    void start();
};

class RealFrameHandler : public FrameHandler
{
	Q_OBJECT    
public:
    explicit RealFrameHandler();
    void reset();

private:
    QByteArray  	mBuffer;
	long			frameCounter;
	long			brokenFrame;
    bool            signalTrial;
    bool            signalStart;
    void			handle();
    int				decodeTrackingMode(const unsigned char* b)	{ return (*b & 0x1C) >> 2; }
    int             decodeTimeMode(const unsigned char* b)		{ return (*b & 0x40) >> 6; }
//    int             decodePointingMode(const unsigned char* b)	{ return (*b & 0x10) >> 4; }
//    int             decodeRespSignal(const unsigned char* b)	{ return *b & 0x01; }
    QDateTime       decodeTime(const unsigned char* b);
	double			decodeAngle(const unsigned char* b);
//	unsigned char	crcKama(unsigned char *b, unsigned int len);
    void            handleServiceFrame();

public slots:
	void			receiveChar(unsigned char ch);
    void            receiveTable(PointingTab) {;}
};

class RotatingFrameHandler : public FrameHandler
{
    Q_OBJECT
    QTimer* timer;
public:
    explicit RotatingFrameHandler();
public slots:
    void receiveChar(unsigned char ch);
    void receiveTable(PointingTab) {;}
private slots:
    void timerOverflow();
};

class ImitationFrameHandler : public FrameHandler
{
    QTimer* timer;
    QQueue<Frame> frameQueue;
    Q_OBJECT
public:
    explicit ImitationFrameHandler();
public slots:
    void receiveChar(unsigned char ch) {;}
    void receiveTable(PointingTab pt);
private slots:
    void timerOverflow();
};

QSharedPointer<FrameHandler> createRealFrameHandler();
QSharedPointer<FrameHandler> createRotatingFrameHandler();
QSharedPointer<FrameHandler> createImitationFrameHandler();

#endif /* FRAMEHANDLER_H_ */
