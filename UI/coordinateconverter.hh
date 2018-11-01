#ifndef COORDINATECONVERTER_HH
#define COORDINATECONVERTER_HH

#include "cubecoordinate.hh"

using Common::CubeCoordinate;

namespace Student {

struct CartesianCoordinate {
  double x;
  double y;

  CartesianCoordinate() {
    x = 0;
    y = 0;
  }

  CartesianCoordinate(double x, double y) {

    this->x = x;
    this->y = y;
  }
};

CartesianCoordinate convertCubeCoordinatesToCartesian(CubeCoordinate cubeCoord);

} // namespace Student

#endif // COORDINATECONVERTER_HH
