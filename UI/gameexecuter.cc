#include "gameexecuter.hh"
#include "actor.hh"
#include "gameexception.hh"
#include <QDebug>
#include <iostream>
#include <vector>
#include "illegalmoveexception.hh"
#include <algorithm>

namespace Student {

GameExecuter::GameExecuter(
    std::shared_ptr<Common::IGameRunner> gameRunner,
    std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState,
    SpinnerContainerWidget *spinnerWidget,
    std::vector<std::shared_ptr<Common::IPlayer>> playerVector)
    : gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState),
      spinnerWidget_(spinnerWidget), playerVector_(playerVector),
      selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false),
      isWheelSpun_(false), selectedActorId_(-1), spunActorMoves_(std::string())
{

  connect(gameBoard_->getBoardWidget(), &GameBoardWidget::hexClicked, this,
          &GameExecuter::handleHexClick);
  connect(spinnerWidget_, &SpinnerContainerWidget::spinningFinished, this,
          &GameExecuter::handleSpin);
  gameState->changePlayerTurn(1);
  gameState->changeGamePhase(Common::GamePhase::MOVEMENT);
  // testikoodia
  gameBoard->addPawn(1, 1);
  gameBoard->addPawn(0, 2);
  gameBoard->addPawn(1, 3);
}

bool GameExecuter::isPlayerPawnsInHex(Common::CubeCoordinate coord) {
  std::vector<std::shared_ptr<Common::Pawn>> playerPawns =
      getPlayerPawnsInCoordinate(coord);
  return (playerPawns.size() != 0);
}

std::vector<std::shared_ptr<Common::Pawn>>
GameExecuter::getPlayerPawnsInCoordinate(Common::CubeCoordinate coord) {
  std::vector<std::shared_ptr<Common::Pawn>> pawnsInClickedHex =
      gameBoard_->getHex(coord)->getPawns();
  std::vector<std::shared_ptr<Common::Pawn>> playerPawns;
  for (auto const &pawn : pawnsInClickedHex) {
    if (pawn->getPlayerId() == gameState_->currentPlayer()) {
      playerPawns.push_back(pawn);
    }
  }
  return playerPawns;
}

bool GameExecuter::trySelectActor(std::string actorType,
                                  Common::CubeCoordinate coord) {
  for (auto const &a : gameBoard_->getHex(coord)->getActors()) {
    if (a->getActorType() == actorType) {
      selectedActorId_ = a->getId();
      return true;;
    }
  }
  selectedActorId_ = -1;
  return false;
}

bool GameExecuter::trySelectTransport(std::string type, Common::CubeCoordinate coord)
{
    for(auto const &t : gameBoard_->getHex(coord)->getTransports()){
        if(t->getTransportType() == type){
            selectedActorId_ = t->getId();
            return true;
        }
    }
    selectedActorId_ = -1;
    return false;
}

bool GameExecuter::tryMoveActor(Common::CubeCoordinate to)
{
    if(gameRunner_->checkActorMovement(selectedHexCoordinates_, to, selectedActorId_, spunActorMoves_)){
        gameRunner_->moveActor(selectedHexCoordinates_, to, selectedActorId_, spunActorMoves_);
        return true;
    }
    return false;
}

bool GameExecuter::tryMoveTransport(Common::CubeCoordinate to)
{
    std::shared_ptr<Common::Hex> selectedHex = gameBoard_->getHex(selectedHexCoordinates_);
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(to);

    std::vector<std::shared_ptr<Common::Transport>> hexTransports = selectedHex->getTransports();
    if(hexTransports.size()!=0){
        for(auto const& transport : hexTransports){
            if(transport->canMove(getCurrentPlayer()->getPlayerId())){
                gameBoard_->moveTransport(transport->getId(), to);
                return true;
            }
        }
    }
    return false;
}

bool GameExecuter::tryFlipTile(Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);
    try{
        std::string actor = gameRunner_->flipTile(coord);
        //if was actor in clicked hex and it can do
        if(tryDoActor(actor, coord)){
            return true;
        }
        //if was transport in clicked hex
        if(putPawnsToTransport(actor, coord)){
            return true;
        }
    }
    catch(Common::IllegalMoveException& e){
        qDebug() << "Et voi kääntää klikkaamaasi ruutua";
        return false;
    }
}

bool GameExecuter::tryDoActor(std::string type, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
    for (auto const &a : hexInCoord->getActors()) {
        if (a->getActorType() == type) {
        a->doAction();
        // TODO: Maybe should handle pawn changes?
        // Actor::doaction(); not implemented yet so I am not sure what should
        // do...
        gamePhaseToSpinning();
        return true;
        }
    }
    return false;
}

void GameExecuter::gamePhaseToMovement()
{
    isWheelSpun_ = false;
    isHexSelected_ = false;
    gameState_->changeGamePhase(Common::GamePhase::MOVEMENT);
    if (playerVector_.back()->getPlayerId()==getCurrentPlayer()->getPlayerId()){
        gameState_->changePlayerTurn(playerVector_.front()->getPlayerId());
        playerVector_.front()->setActionsLeft(3);
    }
    else{
        for(size_t t = 0; t < playerVector_.size()-1; ++t){
            int i = static_cast<int>(t);
            if(playerVector_.at(i)->getPlayerId()==getCurrentPlayer()->getPlayerId()){
                gameState_->changePlayerTurn(playerVector_.at(i+1)->getPlayerId());
                playerVector_.at(i+1)->setActionsLeft(3);
                return;
            }
        }
    }
}

bool GameExecuter::putPawnsToTransport(std::string type, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
    for (auto const &t : hexInCoord->getTransports()){
        if(t->getTransportType() == type){
            for(auto const &pawn : hexInCoord->getPawns()){
                t->addPawn(pawn);
            }
            return true;
        }
    }
    return false;
}

void GameExecuter::gamePhaseToSpinning() {
  isWheelSpun_ = false;
  isHexSelected_ = false;
  gameState_->changeGamePhase(Common::GamePhase::SPINNING);
  std::pair<std::string, std::string> spinResult = gameRunner_->spinWheel();
  spunActorType_ = spinResult.first;
  spunActorMoves_ = spinResult.second;
  spinnerWidget_->beginSpin(spinResult.first, spinResult.second);
  if(!gameBoard_->isAnyActorsOrTransportsOfType(spunActorType_)){
      gamePhaseToMovement();
      return;
  }
}

std::shared_ptr<Common::IPlayer> GameExecuter::getCurrentPlayer() {
  for (auto player : playerVector_) {
    if (player->getPlayerId() == gameState_->currentPlayer()) {
      return player;
    }
  }
  return nullptr;
}

void GameExecuter::tryMovePawn(Common::CubeCoordinate to) {
  // take all current player pawns and try to move them one by one.
  // if move succes, unselect selected hex, update moves left and move pawn.
  std::vector<std::shared_ptr<Common::Pawn>> playerPawnsInSelected =
      getPlayerPawnsInCoordinate(selectedHexCoordinates_);
  if (playerPawnsInSelected.size() != 0) {
    for (auto const &pawn : playerPawnsInSelected) {
      int movesLeft = gameRunner_->checkPawnMovement(selectedHexCoordinates_,
                                                     to, pawn->getId());
      if (movesLeft >= 0) {
        gameRunner_->movePawn(selectedHexCoordinates_, to, pawn->getId());
        getCurrentPlayer()->setActionsLeft(movesLeft);

        break;
      }
    }
  }
  isHexSelected_ = false;
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates) {
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coordinates);

    switch (gameState_->currentGamePhase()) {
        case Common::GamePhase::MOVEMENT :
            if (clickedHex == nullptr) {
              throw Common::GameException(
                  "Clicked hex not exist in game-executer gameboard_");
            } else if (!isHexSelected_) {
                if (isPlayerPawnsInHex(coordinates)) {
                selectedHexCoordinates_ = coordinates;
                isHexSelected_ = true;
                }
            }
            else if (isHexSelected_) {
                if (selectedHexCoordinates_.operator==(coordinates)) {
                    isHexSelected_ = false;
                }
                else {
                    //TODO: Player must able to choose if he move transport or only pawns
                    //Current implement try first move actor, then pawns if actor cant move
                    if(!tryMoveTransport(coordinates)){
                        tryMovePawn(coordinates);
                    }
                }
            }
            if (getCurrentPlayer()->getActionsLeft()==0) {
              gameState_->changeGamePhase(Common::GamePhase::SINKING);
            }
        break;

        case Common::GamePhase::SINKING :
            if(tryFlipTile(coordinates)){
                gamePhaseToSpinning();
            }
        break;

        case Common::GamePhase::SPINNING :
            if (isWheelSpun_) {
                if (!isHexSelected_) {
                    if(trySelectActor(spunActorType_, coordinates)){
                        selectedHexCoordinates_ = coordinates;
                        isHexSelected_ = true;
                    }
                    else if(trySelectTransport(spunActorType_, coordinates)){
                        selectedHexCoordinates_ = coordinates;
                        isHexSelected_ = true;
                    }
                }
                else {
                    if (selectedHexCoordinates_.operator==(coordinates)) {
                        isHexSelected_ = false;
                    }else{
                        if (tryMoveActor(coordinates)){
                            gamePhaseToMovement();
                        }
                        else if(tryMoveTransport(coordinates)){
                            gamePhaseToMovement();
                        }
                        else{
                            qDebug() << "Cannot move actor to clicked hex";
                        }
                    }
                }
            }
        break;
    }
}

void GameExecuter::handleSpin() {
    isWheelSpun_ = true;
}

} // namespace Student
