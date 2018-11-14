#include "gameboard.hh"
#include "actor.hh"
#include "hex.hh"
#include "pawn.hh"
#include "transport.hh"
#include <QDebug>
#include <QObject>

using Common::Actor;
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
  _boardWidget->drawHexagon(newHex->getCoordinates());

  //Next made because testing, not final implementation
  int newId = rand() % 100000 + 1;
  addPawn(1,newId);
  movePawn(newId, newHex->getCoordinates());
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
  Common::CubeCoordinate pawnOldCoord = pawn->getCoordinates();
  _hexMap.at(pawnOldCoord)->removePawn(pawn);
  pawn->setCoordinates(pawnCoord);
  auto newHex = getHex(pawnCoord);
  newHex->addPawn(pawn);
}

void GameBoard::removePawn(int pawnId) {
  shared_ptr<Pawn> pawn = _pawnsByIds[pawnId];
  Common::CubeCoordinate pawnCoords = pawn->getCoordinates();
  _hexMap.at(pawnCoords)->removePawn(pawn);
  _pawnsByIds.erase(pawnId);
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord) {
    _actorsByIds[actor->getId()] = actor;
    actor->addHex(_hexMap.at(actorCoord));
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord) {
  shared_ptr<Actor> actor = _actorsByIds[actorId];
  shared_ptr<Hex> hex = getHex(actorCoord);
  actor->move(hex);
}

void GameBoard::removeActor(int actorId) {
    _actorsByIds.erase(actorId);
    //TODO: remove actor from hex
    //requires actor.getHex() function implemented to actor or actor.remove
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
    //TODO: remove transport from hex
    //requires transport.getHex() function implemented or transport.remove
    transportsByIds_.erase(id);
}

std::vector<std::shared_ptr<Common::Pawn> > GameBoard::getPlayerPawnsInCoordinate(Common::CubeCoordinate coord, int playerId)
{
    std::vector<std::shared_ptr<Common::Pawn>> playerPawns;
    for(auto const &pawn : _pawnsByIds){
        if(coord.operator==(pawn.second->getCoordinates())){
            if(pawn.second->getPlayerId() == playerId){
                playerPawns.push_back(pawn.second);
            }
        }
    }
    return playerPawns;
}

} // namespace Student
