#include <QString>
#include <QtTest>
#include <../../convertation.h>

class PointingsTableTest : public QObject
{
    Q_OBJECT

public:
    PointingsTableTest();

private Q_SLOTS:
    void testDecToDeg();
    void testConvertPointingsToString();
};

PointingsTableTest::PointingsTableTest()
{
}

void PointingsTableTest::testDecToDeg()
{
  DecToDeg etalon = { 1, 15, 30 };

  DecToDeg got = decToDeg(1.25 + 0.00833333333333);

  QCOMPARE(got.deg, etalon.deg);
  QCOMPARE(got.min, etalon.min);
  QCOMPARE(got.sec, etalon.sec);
}

void PointingsTableTest::testConvertPointingsToString()
{
    const std::string etalon = "02.12.14 001_00001_001_01\r\n"
                               "01.02.03,4  05.15  007.45\r\n"
                               "eeeeeeeeeeeeeeeeeeeeeeeee\r\n";
    PointingTab pt;
    pt.time = QTime(1, 2, 3);
    PT_ITEM item;
    item.timeFromStart = 0.4;
    item.azimuth = 7.75;
    item.elevation = 5.25;
    pt.pointingTable.append(item);

    const std::string got = convertPointingsToString(pt);

    QCOMPARE(QString::fromStdString(got), QString::fromStdString(etalon));
}

QTEST_APPLESS_MAIN(PointingsTableTest)

#include "tst_pointingstabletest.moc"
