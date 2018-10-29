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
  if (hex == nullptr)
    return -1;
  else
    return hex->getPawns();
}

bool GameBoard::isWaterTile(CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHex(tileCoord);
  if (hex == nullptr)
    return false;
  else
    return hex->isWaterTile();
}

shared_ptr<Hex> GameBoard::getHex(CubeCoordinate hexCoord) const {

  auto hexIterator = _hexMap.find(hexCoord);
  if (hexIterator == _hexMap.end())
    return nullptr;
  else
    return hexIterator->second;
}

void GameBoard::addHex(shared_ptr<Common::Hex> newHex) {
  _hexMap[newHex->getCoordinates()] = newHex;
}

void GameBoard::addPawn(int playerId, int pawnId) {
  auto pawn = std::make_shared<Common::Pawn>();
  pawn->setId(pawnId, playerId);
  CubeCoordinate coordinates(0, 0, 0);
  pawn->setCoordinates(coordinates);
  _pawnsByIds[pawnId] = pawn;
  auto centerHex = getHex(coordinates);
  centerHex->addPawn(pawn);
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord) {
  shared_ptr<Pawn> pawn = _pawnsByIds[pawnId];
  pawn->setCoordinates(pawnCoord);
  // TODO: remove from current hex
  auto newHex = getHex(pawnCoord);
  newHex->addPawn(pawn);
}

void GameBoard::removePawn(int pawnId) {
  shared_ptr<Pawn> pawn = _pawnsByIds[pawnId];
  // TODO: commented, because Pawn::getCoordinates does not exist
  // CubeCoordinate coordinates = pawn->getCoordinates();
  // shared_ptr<Hex> hex = getHex(coordinates);
  // if (hex != nullptr)
  //   hex->changeOccupation(-1);
  _pawnsByIds.erase(pawnId);
}

} // namespace Student
