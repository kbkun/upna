#include "pointingtable.h"

PointingTable::PointingTable(QObject *parent) :
    QObject(parent)
    ,errString("")
    ,isVal(true)
{

}

void PointingTable::addPointitgItem(PT_ITEM i)
{
    pt.pointingTable.append(i);
    check();
}

void PointingTable::addCalibrationItem(CT_ITEM i)
{
    ct.append(i);
}

void PointingTable::check()
{
    int lastIndex = pt.pointingTable.size() - 1;
    if(lastIndex < 1) return;
    PT_ITEM lastItem = pt.pointingTable.at(lastIndex);
    PT_ITEM prelastItem = pt.pointingTable.at(lastIndex - 1);
    double deltaT = lastItem.timeFromStart - prelastItem.timeFromStart;
    double deltaA = lastItem.azimuth - prelastItem.azimuth;
    double deltaE = lastItem.elevation - prelastItem.elevation;
    double dA = deltaA / deltaT;
    double dE = deltaE / deltaT;
    if(abs(dA) > 18) {
        isVal = false;
        QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) скорость движения по азимуту превышает 18 град/с\n",
                                        lastItem.timeFromStart, lastItem.azimuth, lastItem.elevation);
        errString.append(err);
    }
    if(abs(dE) > 9) {
        isVal = false;
        QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) скорость движения по углу места превышает 9 град/с\n",
                                        lastItem.timeFromStart, lastItem.azimuth, lastItem.elevation);
        errString.append(err);
    }
    if(lastItem.elevation < 2 && dE < -2) {
        isVal = false;
        QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) движение на нижний упор с недопустимой скоростью\n",
                                        lastItem.timeFromStart, lastItem.azimuth, lastItem.elevation);
        errString.append(err);
    }
    if(lastItem.elevation > 86.5 && dE > 2) {
        isVal = false;
        QString err = QString().sprintf("В точке (%.2f, %.3f, %.3f) движение на верхний упор с недопустимой скоростью\n",
                                        lastItem.timeFromStart, lastItem.azimuth, lastItem.elevation);
        errString.append(err);
    }
}

void PointingTable::clearPointings()
{
    pt.time = QDateTime();
    pt.objectType.clear();
    pt.pointingTable.clear();
    errString.clear();
    isVal = true;
}

void PointingTable::clearCalibrations()
{
    ct.clear();
}
