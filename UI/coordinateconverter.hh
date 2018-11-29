#ifndef COORDINATECONVERTER_HH
#define COORDINATECONVERTER_HH

#include "cubecoordinate.hh"

namespace Student {

///
/// \brief Struct for describing normal xy-coordinates
///
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

///
/// \brief Converts CubeCoordinate to CartesianCoordinate
///
CartesianCoordinate convertCoordinates(Common::CubeCoordinate cubeCoord);

} // namespace Student

#endif // COORDINATECONVERTER_HH
