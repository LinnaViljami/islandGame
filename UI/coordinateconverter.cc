#include "coordinateconverter.hh"
#include "math.h"

namespace Student {

CartesianCoordinate convertCoordinates(Common::CubeCoordinate cubeCoord) {

  static const double xFactor = sqrt(3) / 2;
  double cartesianX = (cubeCoord.x - cubeCoord.y) * xFactor;
  double cartesianY = -cubeCoord.z + (static_cast<double>(cubeCoord.x + cubeCoord.y) / 2);
  return CartesianCoordinate(cartesianX, cartesianY);
}

} // namespace Student
