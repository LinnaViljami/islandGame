#include "gameboard.hh"
#include "hex.hh"
#include "pawn.hh"

using Common::CubeCoordinate;
using Common::Hex;
using Common::Pawn;
using std::map;
using std::shared_ptr;

namespace Student {

int GameBoard::checkTileOccupation(CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHex(tileCoord);
  if (hex == nullptr) {
    return -1;
  } else {
    return hex->getPawns();
  }
}

bool GameBoard::isWaterTile(CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHex(tileCoord);
  if (hex == nullptr) {
    return false;
  } else {
    return hex->isWaterTile();
  }
}

shared_ptr<Hex> GameBoard::getHex(CubeCoordinate hexCoord) const {

  auto hexIterator = _hexMap.find(hexCoord);
  if (hexIterator == _hexMap.end()) {
    return nullptr;
  } else {
    return hexIterator->second;
  }
}

void GameBoard::addHex(shared_ptr<Common::Hex> newHex) {
  _hexMap[newHex->getCoordinates()] = newHex;
}

void GameBoard::addPawn(int playerId, int pawnId) {
  auto pawn = std::make_shared<Common::Pawn>();
  pawn->setId(pawnId, playerId);
  _pawnsByIds[pawnId] = pawn;
  auto centerHex = getCenterHex();
  centerHex->addPawn(pawn);
}

shared_ptr<Common::Hex> GameBoard::getCenterHex() const {
  return getHex(CubeCoordinate(0, 0, 0));
}

} // namespace Student
