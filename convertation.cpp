#include "convertation.h"
#include <math.h>
#include <iomanip>
#include <sstream>

DecToDeg decToDeg(double d)
{
    int sign = d > 0 ? 1 : -1;
    DecToDeg res;
    res.deg = d;
    res.min = abs((d - res.deg) * 60);
    res.sec = abs(round(((d - res.deg) * 60.0 - sign * res.min) * 60));
    if(res.sec == 60) {
        res.sec = 0;
        ++res.min;
    }

    return res;
}

const std::string convertPointingsToString(const PointingTab& pointingTab)
{
    std::ostringstream buf;
    const std::string lineEnd = "\r\n";

    buf << QDate::currentDate().toString("dd.MM.yy").toStdString() << " 001_00001_001_01" << lineEnd;

    QVector<PT_ITEM>::const_iterator it = pointingTab.pointingTable.begin();
    for(; it != pointingTab.pointingTable.end(); ++it) {
        const double secs = it->timeFromStart;
        const int integerSecs = floor(secs);
        const double fractionalSecs = secs - integerSecs;
        const int tenthSecs = fractionalSecs * 10;

        const QDateTime mskTime = pointingTab.time.addSecs(integerSecs);

        const DecToDeg el = decToDeg(it->elevation);
        const DecToDeg az = decToDeg(it->azimuth);

        buf << mskTime.toString("hh.mm.ss").toStdString() << "," << tenthSecs << "  ";
        buf << std::setfill('0') << std::setw(2) << el.deg << '.' << std::setw(2) << el.min << "  ";
        buf << std::setfill('0') << std::setw(3) << az.deg << '.' << std::setw(2) << az.min << lineEnd;
    }
    buf << "eeeeeeeeeeeeeeeeeeeeeeeee" << lineEnd;

    return buf.str();
}
