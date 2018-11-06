#include "gameboard.hh"
#include "actor.hh"
#include "hex.hh"
#include "pawn.hh"

using std::shared_ptr;
using Common::Pawn;
using Common::CubeCoordinate;
using std::map;
using Common::Actor;

namespace Student {

GameBoard::GameBoard(GameBoardWidget *boardWidget)
    : _boardWidget(boardWidget) {}

int GameBoard::checkTileOccupation(CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHex(tileCoord);
  if (hex == nullptr)
    return -1;
  else
    return hex->getPawnAmount();
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

  _boardWidget->drawHexagon(newHex->getCoordinates());
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
  // TODO: remove from current hex?
  auto newHex = getHex(pawnCoord);
  newHex->addPawn(pawn);
}

void GameBoard::removePawn(int pawnId) {
  shared_ptr<Pawn> pawn = _pawnsByIds[pawnId];
  // TODO: remove from current hex?
  _pawnsByIds.erase(pawnId);
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord) {
  shared_ptr<Actor> actor = _actorsByIds[actorId];
  shared_ptr<Hex> hex = getHex(actorCoord);
  actor->move(hex);
}

void GameBoard::removeActor(int actorId) { _actorsByIds.erase(actorId); }

} // namespace Student
