#ifndef FRAME_H
#define FRAME_H

#include <QDateTime>

const unsigned char F_START = 235;  /*маркер начала кадра*/
const unsigned char F_END = 156;    /*маркер конца кадра*/

struct Frame {
    int         timeMode;
//    int         respSignal;
//    int         pointingMode;
    QDateTime   time;
    int         trackingMode;
    double      azimuth;
    double      elevation;
};

#endif // FRAME_H
