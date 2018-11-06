#include "coordinateconverter.hh"
#include "cubecoordinate.hh"
#include "math.h"
#include <QString>
#include <QtTest>

using Common::CubeCoordinate;
using Student::CartesianCoordinate;

Q_DECLARE_METATYPE(CubeCoordinate);
Q_DECLARE_METATYPE(CartesianCoordinate);

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
  QFETCH(CubeCoordinate, cubeCoord);
  QFETCH(CartesianCoordinate, excepted);

  CartesianCoordinate actual =
      Student::convertCoordinates(cubeCoord);

  QCOMPARE(actual.x, excepted.x);
  QCOMPARE(actual.y, excepted.y);
}

void CoordinateConverterTests::testCoordinateConverting_data() {
  QTest::addColumn<CubeCoordinate>("cubeCoord");
  QTest::addColumn<CartesianCoordinate>("excepted");

  QTest::newRow("center") << CubeCoordinate(0, 0, 0)
                          << CartesianCoordinate(0.0, 0.0);
  QTest::newRow("along cube Z-axis")
      << CubeCoordinate(+2, -2, 0) << CartesianCoordinate(4 * sqrt(3) / 2, 0.0);
  QTest::newRow("random point 1") << CubeCoordinate(+2, -1, -1)
                                  << CartesianCoordinate(3 * sqrt(3) / 2, 1.5);
  QTest::newRow("random point 2")
      << CubeCoordinate(-3, 0, +3)
      << CartesianCoordinate(-3 * sqrt(3) / 2, -4.5);
  QTest::newRow("random point 3")
      << CubeCoordinate(-3, +2, +1)
      << CartesianCoordinate(-5 * sqrt(3) / 2, -1.5);
}

QTEST_APPLESS_MAIN(CoordinateConverterTests)

#include "coordinateconvertertests.moc"
