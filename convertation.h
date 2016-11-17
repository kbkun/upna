#ifndef CONVERTATION_H
#define CONVERTATION_H

#include <QtGlobal>
#include "pointingtable.h"

typedef struct _DecToDeg {
    qint16 deg;
    qint16 min;
    qint16 sec;
} DecToDeg;

DecToDeg decToDeg(double d);
const std::string convertPointingsToString(const PointingTab& pointingTab);

#endif // CONVERTATION_H
