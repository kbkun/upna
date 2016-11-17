#include "framehandler.h"
#include "crc.h"
#include <QDebug>

FrameHandler::~FrameHandler()
{
}

QSharedPointer<FrameHandler> createRealFrameHandler()
{
    return QSharedPointer<FrameHandler>(new RealFrameHandler);
}

QSharedPointer<FrameHandler> createRotatingFrameHandler()
{
    return QSharedPointer<FrameHandler>(new RotatingFrameHandler);
}

QSharedPointer<FrameHandler> createImitationFrameHandler()
{
    return QSharedPointer<FrameHandler>(new ImitationFrameHandler);
}


RealFrameHandler::RealFrameHandler()
    : frameCounter(0)
    , brokenFrame(0)
    , signalTrial(false)
    , signalStart(false)
{
}


void RealFrameHandler::receiveChar(unsigned char ch)
{
    qDebug() << QString::number(ch);
    if(mBuffer.endsWith(F_END)) {
        mBuffer.append(ch);
        handle();
        return;
    }
    mBuffer.append(ch);
}

void RealFrameHandler::handle()
{
    /*чистим мусор*/
    int p = mBuffer.indexOf(F_START);
    if(p) mBuffer = mBuffer.remove(0, p);
/*
 * 	проверка контрольной суммы принятого кадра
 */
//    unsigned char crc = kama::crc((unsigned char*)mBuffer.data(), mBuffer.size() - 1);
//    if(!mBuffer.endsWith(crc)) {
//        qDebug() << QString(tr("Неверная контрольная сумма"));
//        brokenFrame++;
//        mBuffer.clear();
//        return;
//    }
/*
 * проверка признака типа информации
 * 		0x0F - кадр с измерительной информацией
 * 		0x03 - кадр без измерительной информации
 */
    if(mBuffer.at(3) == 0x03) {
        handleServiceFrame();
        return;
	}
    if(signalTrial) {
        emit start();
        signalTrial = false;
        qDebug() << QString(tr("Старт!"));
    }
	frameCounter++;
    frame.timeMode = decodeTimeMode((unsigned char*)mBuffer.data() + 8);
    frame.time = decodeTime((unsigned char*)mBuffer.data() + 8);
    frame.trackingMode = decodeTrackingMode((unsigned char*)mBuffer.data() + 5);
    frame.azimuth = decodeAngle((unsigned char*)mBuffer.data() + 11);
    frame.elevation = decodeAngle((unsigned char*)mBuffer.data() + 18);

//    qDebug() << "time mode: " << frame.timeMode;
//    qDebug() << "time: " << frame.time;
//    qDebug() << "tracking mode: " << frame.trackingMode;
//    qDebug() << "azimuth" << frame.azimuth;
//    qDebug() << "elevation" << frame.elevation;
//    qDebug() << "--------------------------------------";

    mBuffer.clear();
    emit readyToSend(frame);
}

//int FrameHandler::decodeTrackingMode(const unsigned char* b)
/*
 * декодирует условия сопровождения в канале углов
 * --------------------------------------------------------------------------------------------------------------
 * | № байта | 				биты					    | 					Информация							|
 * | в кадре | 7	6	5	|	4	3	2	|	1	0	|													 	|
 * --------------------------------------------------------------------------------------------------------------
 * |		 |											|	000 - РУ            								|
 * |         |                                          |   110 - РУ скор                                       |
 * |		 |											|	001 - АС по Аз. РУ по УМ                         	|
 * |	5	 | 0	0	0	| канал углов	|	0	0	|	010	- АС                        					|
 * |		 |											|	100 - ПН                                        	|
 * |		 |											|	101 - ЦУк                               			|
 * --------------------------------------------------------------------------------------------------------------
 */
//{
//	int mode = *b & 0x1C >> 2; /* 0x1C = 0b00011100 */
//	return mode;
//}

QDateTime RealFrameHandler::decodeTime(const unsigned char* b)
/*
 * декодирует значение времени в принятом кадре первчной информации
 * --------------------------------------------------------------------------------------------------------------
 * | № байта | 							биты								    | 	Информация					|
 * | в кадре | 7		6		5		4		3		2		1		0		|							 	|
 * --------------------------------------------------------------------------------------------------------------
 * |   8     | 0		Пр		0		2^16	2^15	2^14	2^13	2^12	| Время проведения измерений 	|
 * |   9     | 0		2^11	2^10	2^9		2^8		2^7		2^6		2^5		| 2^0 = 1 сек				 	|
 * |   10    | 0		2^4		2^3		2^2		2^1		2^0		2^-1	2^-2	| Пр - признак отсчёта времени:	|
 * |		 |																	|	- "1" - московское время	|
 * |		 |																	|	- "0" - стартовое время		|
 * --------------------------------------------------------------------------------------------------------------
 */
{
    QDateTime time;
	uint16_t t, tmp1, tmp2, tmp3, tmp4;
    char /*sign, */hour, min, sec;
    int ms;
	tmp1 = *b << 12;
	tmp2 = *(b+1) << 5;
	tmp3 = *(b+2) >> 2;
	tmp4 = *(b+2) & 0x03;
	t = tmp1 + tmp2 + tmp3;
	hour = t / 3600;
	min = (t / 3600.0 - hour) * 60;
	sec = t - hour * 3600 - min * 60;
    ms = tmp4 == 0 ? 0 : 250 * tmp4;
	if(sec == 60) {
		sec = 0;
		min++;
	}
	if(min == 60) {
		min = 0;
		hour++;
	}
    if(hour == 24) hour = 0;
    time.setDate(QDate::currentDate());
    QTime tmpTime;
    tmpTime.setHMS(hour, min, sec, ms);
    time.setTime(tmpTime);
//    time.setHMS(hour, min, sec, ms);

	return time;
}

double RealFrameHandler::decodeAngle(const unsigned char* b)
/*
 * декодирует значение угла в принятом кадре первчной информации
 * ------------------------------------------------------------------------------------------------------
 * | № байта | 							биты								    | 	Информация          |
 * | в кадре | 7		6		5		4		3		2		1		0		|                       |
 * -------------------------------------------------------------------------------------------------------
 * |   11    | 0		0		0		0		0		2^14	2^13	2^12	| Азимут                |
 * |   12    | 0		2^11	2^10	2^9		2^8		2^7		2^6		2^5		| 2^0 = 180 град * 2^-14|
 * |   13    | 0		2^4		2^3		2^2		2^1		2^0		0		0		|                       |
 * -------------------------------------------------------------------------------------------------------
 * |   18    | 0		знак	0		0		0		2^14	2^13	2^12	| Угол места            |
 * |   19    | 0		2^11	2^10	2^9		2^8		2^7		2^6		2^5		| 2^0 = 180 град * 2^-14|
 * |   20    | 0		2^4		2^3		2^2		2^1		2^0		0		0		|                       |
 * -------------------------------------------------------------------------------------------------------
 */
{
	double angle;
	char sign;
	uint16_t tmp1, tmp2, tmp3;
	sign = (*b & 0x40) == 0 ? 1 : -1;
	tmp1 = *b << 12;
	tmp2 = *(b+1) << 5;
	tmp3 = *(b+2) >> 2;
	angle = sign * (tmp1 + tmp2 + tmp3) * 0.010986328125;	/* 180 * 2^-14 =  0.010986328125 */
	return angle;
}

void RealFrameHandler::handleServiceFrame()
{
    static int c = 0;
    qDebug() << QString::number(mBuffer.at(5)) << " " << QString::number(mBuffer.at(6)) << " " << QString::number(mBuffer.at(7));
    if((unsigned char)mBuffer.at(5) == 65
            && (unsigned char)mBuffer.at(6) == 65
            && (unsigned char)mBuffer.at(7) == 65) {
        qDebug() << QString(tr("Служебный кадр №2"));
        mBuffer.clear();
        return;
    }
    ++c;
    qDebug() << QString(tr("Служебный кадр №1 ")) + QString::number(c);
    if(c == 3) {
        c = 0;
        signalTrial = true;
        mBuffer.clear();
        qDebug() << QString(tr("Протяжка!"));
    }
}

void RealFrameHandler::reset()
{

}

RotatingFrameHandler::RotatingFrameHandler()
    : timer(new QTimer(this))
{
    frame.azimuth = 0;
    frame.elevation = 7;
    frame.timeMode = 1;
    frame.trackingMode = 0;
    connect(timer, SIGNAL(timeout()), SLOT(timerOverflow()));
    timer->start(250);
}

void RotatingFrameHandler::receiveChar(unsigned char ch)
{

}

void RotatingFrameHandler::timerOverflow()
{
    frame.time.setDate(QDate::currentDate());
    frame.time.setTime(QTime::currentTime());
    frame.azimuth += 0.987;
    if(frame.azimuth >= 360) frame.azimuth -= 360;
    emit readyToSend(frame);
}

ImitationFrameHandler::ImitationFrameHandler()
    : timer(new QTimer(this))
{

}

void ImitationFrameHandler::receiveTable(PointingTab pt)
{
    if(timer->isActive()) timer->stop();
    frameQueue.clear();
    const int freq = 4;
    int timeMode;
    QDateTime time;
    if(pt.time.isNull()) {
        timeMode = 0;
        time = QDateTime::currentDateTime();
    } else {
        timeMode = 1;
        time = pt.time;
    }
    Frame tmpFrame;
    tmpFrame.timeMode = timeMode;
    tmpFrame.trackingMode = 4;;
    QVector<PT_ITEM>::const_iterator it = pt.pointingTable.begin();
    float dT, timeIncr, intTimeIncr, fracTimeIncr, azimuthIncr, elevationIncr;
    int ticks;
    for(; it != pt.pointingTable.end() - 1; ++it) {
        PT_ITEM curItem = *it;
        PT_ITEM nextItem = *(it+1);
        //находим приращение времени между двумя соседними точками
        dT = nextItem.timeFromStart - curItem.timeFromStart;
        //вычисляем количество кадров, которые будут отправлены в канал связи за время dT
        ticks = freq * dT;
        //вычисляем приращения времени, азимута и угла места за время между отправками кадров
        timeIncr = dT / ticks;
        fracTimeIncr = modff(timeIncr, &intTimeIncr);
        azimuthIncr = (nextItem.azimuth - curItem.azimuth) / ticks;
        elevationIncr = (nextItem.elevation - curItem.elevation) / ticks;
        for(int i = 0; i < ticks; ++i) {
            time = time.addSecs(intTimeIncr).addMSecs(fracTimeIncr * 1000);
            tmpFrame.time = time;
            tmpFrame.azimuth = (int)((curItem.azimuth + azimuthIncr * i) / 0.010986328125) * 0.010986328125;
            tmpFrame.elevation = (int)((curItem.elevation + elevationIncr * i) / 0.010986328125) * 0.010986328125;
            frameQueue.append(tmpFrame);
        }
    }
    PT_ITEM lastItem = pt.pointingTable.last();
    time = time.addSecs(intTimeIncr).addMSecs(fracTimeIncr * 1000);
    tmpFrame.time = time;
    tmpFrame.azimuth = (int)((lastItem.azimuth) / 0.010986328125) * 0.010986328125;
    tmpFrame.elevation = (int)((lastItem.elevation) / 0.010986328125) * 0.010986328125;
    frameQueue.append(tmpFrame);
    connect(timer, SIGNAL(timeout()), SLOT(timerOverflow()));
    timer->start(250);
}

void ImitationFrameHandler::timerOverflow()
{
    if(frameQueue.isEmpty()) {
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(timerOverflow()));
    }
    else {
        Frame tmp = frameQueue.dequeue();
//        QTime t = tmp.time.time();
//        qDebug() <<  t.toString("hh.mm.ss:zzz") << "\t" << tmp.azimuth << "\t" << tmp.elevation;
        emit readyToSend(tmp);
    }
}
