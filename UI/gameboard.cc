#include "gameboard.hh"
#include "actor.hh"
#include "hex.hh"
#include "pawn.hh"
#include "transport.hh"
#include <QDebug>
#include <QObject>
#include <transport.hh>

using Common::Actor;
using Common::Transport;
using Common::CubeCoordinate;
using Common::Hex;
using Common::Pawn;
using std::map;
using std::shared_ptr;

namespace Student {

GameBoard::GameBoard(GameBoardWidget *boardWidget)
    : _boardWidget(boardWidget) {}

GameBoardWidget *GameBoard::getBoardWidget() { return _boardWidget; }

int GameBoard::checkTileOccupation(CubeCoordinate tileCoord) const {
  shared_ptr<Hex> hex = getHex(tileCoord);
  if (hex == nullptr) {
    return -1;
  } else {
    return hex->getPawnAmount();
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
  _boardWidget->addOrUpdateHex(newHex);
}

void GameBoard::addPawn(int playerId, int pawnId) {
  addPawn(playerId, pawnId, CubeCoordinate(0, 0, 0));
}

void GameBoard::addPawn(int playerId, int pawnId,
                        Common::CubeCoordinate coord) {
  auto pawn = std::make_shared<Common::Pawn>();
  pawn->setId(pawnId, playerId);
  pawn->setCoordinates(coord);
  _pawnsByIds[pawnId] = pawn;
  auto hex = getHex(coord);
  hex->addPawn(pawn);
  _boardWidget->addOrUpdatePawn(pawn);
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord) {
  shared_ptr<Pawn> pawn = _pawnsByIds[pawnId];
  Common::CubeCoordinate pawnOldCoord = pawn->getCoordinates();
  _hexMap.at(pawnOldCoord)->removePawn(pawn);
  pawn->setCoordinates(pawnCoord);
  auto newHex = getHex(pawnCoord);
  newHex->addPawn(pawn);
  _boardWidget->movePawn(pawn, pawnOldCoord, pawnCoord);
}

void GameBoard::removePawn(int pawnId) {
  shared_ptr<Pawn> pawn = _pawnsByIds[pawnId];
  Common::CubeCoordinate pawnCoords = pawn->getCoordinates();
  _boardWidget->removePawn(pawn);
  _hexMap.at(pawnCoords)->removePawn(pawn);
  _pawnsByIds.erase(pawnId);
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord) {
  _actorsByIds[actor->getId()] = actor;
  actor->addHex(_hexMap.at(actorCoord));
  _boardWidget->addOrUpdateActor(actor);
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord) {
  shared_ptr<Actor> actor = _actorsByIds[actorId];
  shared_ptr<Hex> targetHex = getHex(actorCoord);
  _boardWidget->moveActor(actor, actor->getHex()->getCoordinates(), actorCoord);
  actor->move(targetHex);
}

void GameBoard::removeActor(int actorId) {
  shared_ptr<Actor> actor = _actorsByIds[actorId];
  _boardWidget->removeActor(actor);
  actor->getHex()->removeActor(actor);
  _actorsByIds.erase(actorId);
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport,
                             Common::CubeCoordinate coord) {
  transportsByIds_[transport->getId()] = transport;
  _hexMap.at(coord)->addTransport(transport);
}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord) {
  transportsByIds_.at(id)->move(_hexMap.at(coord));
}

void GameBoard::removeTransport(int id) {
   shared_ptr<Transport> transport = transportsByIds_[id];
   transport->getHex()->removeTransport(transport);
  transportsByIds_.erase(id);
}

bool GameBoard::isAnyPiecesOfType(std::string type) {
  for (auto const &hex : _hexMap) {
    if (hex.second->getPieceType() == type) {
      return true;
    }
  }
  return false;
}

} // namespace Student
