#ifndef POINTINGTABLE_H
#define POINTINGTABLE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDateTime>
#include <QDebug>

typedef struct {
    double  timeFromStart;
    double  azimuth;
    double  elevation;
} PT_ITEM;

struct PointingTab {
    QDateTime           time;
    QString             objectType;
    QVector<PT_ITEM>    pointingTable;
};

typedef struct {
    double  timeFromStart;
    double  value;
} CT_ITEM;

class PointingTable : public QObject
{
    Q_OBJECT
    PointingTab pt;
    QVector<CT_ITEM> ct;
    QString errString;
    bool isVal;
    void check();
public:
    explicit PointingTable(QObject *parent = 0);
    bool        isValid()                   { return isVal; }
    QString     error()                     { return errString; }
    void        setTime(QDateTime t)        { pt.time = t; }
    QDateTime   getTime()                   { return pt.time; }
    void        setObjectType(QString s)    { pt.objectType = s; }
    QString     getObjectType()             { return pt.objectType; }
    const PointingTab& getPointingTable()   { return pt; }
    const QVector<CT_ITEM>& getCalibrationTable() { return ct; }
    void        addPointitgItem(PT_ITEM i);
    void        addCalibrationItem(CT_ITEM i);
    void        clearPointings();
    void        clearCalibrations();
    QVector<PT_ITEM>::iterator ptBegin()    { return pt.pointingTable.begin(); }
    QVector<PT_ITEM>::iterator ptEnd()      { return pt.pointingTable.end(); }
    QVector<CT_ITEM>::iterator ctBegin()    { return ct.begin(); }
    QVector<CT_ITEM>::iterator ctEnd()      { return ct.end(); }
};

#endif // POINTINGTABLE_H
