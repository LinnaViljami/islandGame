#include "gameboard.hh"

using Common::CubeCoordinate;
using Common::Hex;
using std::map;
using std::shared_ptr;

namespace Student {

int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHexOnCoordinatesOrNull(tileCoord);
  if (hex == nullptr) {
    return -1;
  } else {
    return hex->getPawns();
  }
}

bool GameBoard::isWaterTile(CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHexOnCoordinatesOrNull(tileCoord);
  if (hex == nullptr) {
    return false;
  } else {
    return hex->isWaterTile();
  }
}

shared_ptr<Hex> GameBoard::getHexOnCoordinatesOrNull(
    const Common::CubeCoordinate coordinates) const {
  auto hexIterator = _hexMap.find(coordinates);
  if (hexIterator == _hexMap.end()) {
    return nullptr;
  } else {
    return hexIterator->second;
  }
}

} // namespace Student
