#include "gameboard.hh"
#include "actor.hh"
#include "hex.hh"
#include "pawn.hh"
#include "transport.hh"
#include <QDebug>
#include <QObject>
#include <transport.hh>

using Common::Actor;
using Common::CubeCoordinate;
using Common::Hex;
using Common::Pawn;
using Common::Transport;
using std::map;
using std::shared_ptr;

namespace Student {

GameBoard::GameBoard(GameBoardWidget *boardWidget)
    : boardWidget_(boardWidget) {}

GameBoardWidget *GameBoard::getBoardWidget() { return boardWidget_; }

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

  auto hexIterator = hexMap_.find(hexCoord);
  if (hexIterator == hexMap_.end()) {
    return nullptr;
  } else {
    return hexIterator->second;
  }
}

void GameBoard::addHex(shared_ptr<Common::Hex> newHex) {
  hexMap_[newHex->getCoordinates()] = newHex;
  if (boardWidget_ != nullptr)
    boardWidget_->addOrUpdateHex(newHex);
}

void GameBoard::addPawn(int playerId, int pawnId) {
  addPawn(playerId, pawnId, CubeCoordinate(0, 0, 0));
}

void GameBoard::addPawn(int playerId, int pawnId,
                        Common::CubeCoordinate coord) {
  auto pawn = std::make_shared<Common::Pawn>();
  pawn->setId(pawnId, playerId);
  pawn->setCoordinates(coord);
  pawnsByIds_[pawnId] = pawn;
  auto hex = getHex(coord);
  hex->addPawn(pawn);
  if (boardWidget_ != nullptr)
    boardWidget_->addOrUpdatePawn(pawn);
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord) {
  auto targetHex = getHex(pawnCoord);
  if (targetHex != nullptr) {
    shared_ptr<Pawn> pawn = pawnsByIds_[pawnId];
    Common::CubeCoordinate pawnOldCoord = pawn->getCoordinates();
    hexMap_.at(pawnOldCoord)->removePawn(pawn);
    pawn->setCoordinates(pawnCoord);
    targetHex->addPawn(pawn);
    if (boardWidget_ != nullptr)
      boardWidget_->movePawn(pawn, pawnOldCoord, pawnCoord);
  }
}

void GameBoard::removePawn(int pawnId) {
  shared_ptr<Pawn> pawn = pawnsByIds_[pawnId];
  Common::CubeCoordinate pawnCoords = pawn->getCoordinates();
  if (boardWidget_ != nullptr)
    boardWidget_->removePawn(pawn);
  hexMap_.at(pawnCoords)->removePawn(pawn);
  pawnsByIds_.erase(pawnId);
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord) {
  actorsByIds_[actor->getId()] = actor;
  shared_ptr<Hex> hex = getHex(actorCoord);
  actor->addHex(hex);
  if (boardWidget_ != nullptr)
    boardWidget_->addOrUpdateActor(actor);
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord) {
  shared_ptr<Hex> targetHex = getHex(actorCoord);
  if (targetHex != nullptr) {
    shared_ptr<Actor> actor = actorsByIds_[actorId];
    if (boardWidget_ != nullptr)
      boardWidget_->moveActor(actor, actor->getHex()->getCoordinates(),
                              actorCoord);
    actor->move(targetHex);
  }
}

void GameBoard::removeActor(int actorId) {
  shared_ptr<Actor> actor = actorsByIds_[actorId];
  if (boardWidget_ != nullptr)
    boardWidget_->removeActor(actor);
  actor->getHex()->removeActor(actor);
  actorsByIds_.erase(actorId);
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport,
                             Common::CubeCoordinate coord) {
  auto hex = getHex(coord);
  hex->addTransport(transport);
  transport->move(hex);
  if (boardWidget_ != nullptr)
    boardWidget_->addOrUpdateTransport(transport);
  transportsByIds_[transport->getId()] = transport;
}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord) {
  shared_ptr<Hex> targetHex = getHex(coord);
  if (targetHex != nullptr) {
    shared_ptr<Transport> transport = transportsByIds_.at(id);
    if (boardWidget_ != nullptr)
      boardWidget_->moveTransport(transport,
                                  transport->getHex()->getCoordinates(), coord);
    transport->move(targetHex);
  }
}

void GameBoard::removeTransport(int id) {
  shared_ptr<Transport> transport = transportsByIds_[id];
  if (boardWidget_ != nullptr)
    boardWidget_->removeTransport(transport);
  transport->getHex()->removeTransport(transport);
  transportsByIds_.erase(id);
}

bool GameBoard::isAnyPiecesOfType(std::string type) {
  for (auto const &hex : hexMap_) {
    if (hex.second->getPieceType() == type) {
      return true;
    }
  }
  return false;
}

} // namespace Student
