#include "coordinateconverter.hh"
#include "cubecoordinate.hh"
#include "math.h"
#include <QString>
#include <QtTest>

using Common::CubeCoordinate;
using Student::CartesianCoordinate;

class CoordinateConverterTests : public QObject {
  Q_OBJECT

public:
  CoordinateConverterTests();

private Q_SLOTS:
  void testCoordinateConverting();
  void testCoordinateConverting_data();
};

CoordinateConverterTests::CoordinateConverterTests() {}

void CoordinateConverterTests::testCoordinateConverting() {
  QFETCH(int, cubeX);
  QFETCH(int, cubeY);
  QFETCH(int, cubeZ);
  QFETCH(double, exceptedCartesianX);
  QFETCH(double, exceptedCartesianY);

  CubeCoordinate cubeCoord(cubeX, cubeY, cubeZ);

  CartesianCoordinate actual =
      Student::convertCubeCoordinatesToCartesian(cubeCoord);

  QCOMPARE(actual.x, exceptedCartesianX);
  QCOMPARE(actual.y, exceptedCartesianY);
}

void CoordinateConverterTests::testCoordinateConverting_data() {
  QTest::addColumn<int>("cubeX");
  QTest::addColumn<int>("cubeY");
  QTest::addColumn<int>("cubeZ");
  QTest::addColumn<double>("exceptedCartesianX");
  QTest::addColumn<double>("exceptedCartesianY");

  QTest::newRow("center") << 0 << 0 << 0 << 0.0 << 0.0;
  QTest::newRow("along cube Z-axis") << +2 << -2 << 0 << 4 * sqrt(3) / 2 << 0.0;
  QTest::newRow("random point 1") << +2 << -1 << -1 << 3 * sqrt(3) / 2 << 1.5;
  QTest::newRow("random point 2") << -3 << 0 << +3 << -3 * sqrt(3) / 2 << -4.5;
  QTest::newRow("random point 3") << -3 << +2 << +1 << -5 * sqrt(3) / 2 << -1.5;
}

QTEST_APPLESS_MAIN(CoordinateConverterTests)

#include "coordinateconvertertests.moc"
