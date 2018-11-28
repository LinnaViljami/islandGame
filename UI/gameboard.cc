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
using std::vector;

namespace Student {

GameBoard::GameBoard(GameBoardWidget *boardWidget)
    : boardWidget_(boardWidget) {}

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
  if (boardWidget_ != nullptr) {
    boardWidget_->addOrUpdateHex(newHex);
  }
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
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord) {
  auto targetHex = getHex(pawnCoord);
  if (targetHex != nullptr) {
    shared_ptr<Pawn> pawn = pawnsByIds_[pawnId];
    Common::CubeCoordinate pawnOldCoord = pawn->getCoordinates();
    hexMap_.at(pawnOldCoord)->removePawn(pawn);
    pawn->setCoordinates(pawnCoord);
    targetHex->addPawn(pawn);
  }
}

void GameBoard::removePawn(int pawnId) {
  shared_ptr<Pawn> pawn = pawnsByIds_[pawnId];
  Common::CubeCoordinate pawnCoords = pawn->getCoordinates();
  hexMap_.at(pawnCoords)->removePawn(pawn);
  pawnsByIds_.erase(pawnId);
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord) {
  actorsByIds_[actor->getId()] = actor;
  shared_ptr<Hex> hex = getHex(actorCoord);
  actor->addHex(hex);
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord) {
  shared_ptr<Hex> targetHex = getHex(actorCoord);
  if (targetHex != nullptr) {
    shared_ptr<Actor> actor = actorsByIds_[actorId];
    actor->move(targetHex);
  }
}

void GameBoard::removeActor(int actorId) {
  shared_ptr<Actor> actor = actorsByIds_[actorId];
  actor->getHex()->removeActor(actor);
  actorsByIds_.erase(actorId);
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport,
                             Common::CubeCoordinate coord) {
  auto hex = getHex(coord);
  hex->addTransport(transport);
  transport->move(hex);
  transportsByIds_[transport->getId()] = transport;
}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord) {
  shared_ptr<Hex> targetHex = getHex(coord);
  if (targetHex != nullptr) {
    shared_ptr<Transport> transport = transportsByIds_.at(id);
    transport->move(targetHex);
  }
}

void GameBoard::removeTransport(int id) {
  shared_ptr<Transport> transport = transportsByIds_[id];
  transport->getHex()->removeTransport(transport);
  transportsByIds_.erase(id);
}

bool GameBoard::isAnyPiecesOfType(std::string type) const {
  for (auto const &hex : hexMap_) {
    if (hex.second->getPieceType() == type) {
      return true;
    }
  }
  return false;
}

bool GameBoard::isAnyActorsOrTransportsOfType(std::string type) const {
  for (auto const &actor : actorsByIds_) {
    if (actor.second->getActorType() == type) {
      return true;
    }
  }
  for (auto const &transport : transportsByIds_) {
    if (transport.second->getTransportType() == type) {
      return true;
    }
  }
  return false;
}

bool GameBoard::hasGameEnded() const {
  for (auto &&pair : hexMap_) {
    auto &hex = pair.second;
    std::string pieceType = hex->getPieceType();
    if (pieceType == "Beach" || pieceType == "Forest") {
      return false;
    }
  }
  return true;
}

void GameBoard::initializePawns(vector<shared_ptr<Player>> players) {
  vector<shared_ptr<Hex>> hexes = getAllHexes();
  std::random_shuffle(hexes.begin(), hexes.end());
  static const int PAWN_COUNT = 6;
  int counter = 0;
  for (auto &&player : players) {
    for (int i = 0; i < PAWN_COUNT; ++i) {
      Common::CubeCoordinate coord = hexes.at(counter)->getCoordinates();
      addPawn(player->getPlayerId(), counter, coord);
      ++counter;
    }
  }
}

void GameBoard::updateBoard()
{
    boardWidget_->updateBoard();
}

std::vector<std::shared_ptr<Common::Actor>> GameBoard::getAllActors() const {
  vector<shared_ptr<Actor>> ret;
  for (auto &&pair : actorsByIds_) {
    ret.push_back(pair.second);
  }
  return ret;
}

int GameBoard::getPlayerPawnAmount(int playerId)
{
    int pawnAmount = 0;
    for(auto const& hex : getAllHexes()){
        for(auto const& pawn : hex->getPawns()){
            if(pawn->getPlayerId() == playerId){
                ++pawnAmount;
            }
        }
    }
    return pawnAmount;
}

vector<shared_ptr<Hex>> GameBoard::getAllHexes() const {
  vector<shared_ptr<Hex>> ret;
  for (auto &&pair : hexMap_) {
    auto &hex = pair.second;
    ret.push_back(hex);
  }
  return ret;
}

} // namespace Student
