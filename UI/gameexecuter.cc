#include "gameexecuter.hh"
#include "actor.hh"
#include "gameexception.hh"
#include <QDebug>
#include <iostream>
#include <vector>
#include "illegalmoveexception.hh"

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

void GameExecuter::trySelectActor(std::string actorType,
                                  Common::CubeCoordinate coord) {
  for (auto const &a : gameBoard_->getHex(coord)->getActors()) {
    if (a->getActorType() == actorType) {
      selectedActorId_ = a->getId();
      return;
    }
  }
  selectedActorId_ = -1;
  return;
}

bool GameExecuter::tryMoveTransport(Common::CubeCoordinate to)
{
    std::shared_ptr<Common::Hex> selectedHex = gameBoard_->getHex(selectedHexCoordinates_);
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(to);


    std::vector<std::shared_ptr<Common::Transport>> hexTransports = selectedHex->getTransports();
    if(hexTransports.size()!=0){
        for(auto const& transport : hexTransports){
            if(transport->canMove(getCurrentPlayer()->getPlayerId())){
                transport->move(clickedHex);
                return true;
            }
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
        if (movesLeft == 0) {
          gameState_->changeGamePhase(Common::GamePhase::SINKING);
        }
        break;
      }
    }
  }
  isHexSelected_ = false;
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates) {
  std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coordinates);
  if (gameState_->currentGamePhase() == Common::GamePhase::MOVEMENT) {
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
            if(!tryMoveTransport(coordinates)){
                tryMovePawn(coordinates);
            }
        }
    }
  } else if (gameState_->currentGamePhase() == Common::GamePhase::SINKING) {
        try{
            std::string actor = gameRunner_->flipTile(coordinates);
            //TODO if actor is transport
            for (auto const &a : clickedHex->getActors()) {
                if (a->getActorType() == actor) {
                a->doAction();
                // TODO: Maybe should handle pawn changes?
                // Actor::doaction(); not implemented yet so I am not sure what should
                // do...
                gamePhaseToSpinning();
                break;
                }
            }
        }
        catch(Common::IllegalMoveException& e){
            qDebug() << "Et voi kääntää klikkaamaasi ruutua";
        }
  } else if (gameState_->currentGamePhase() == Common::GamePhase::SPINNING) {
    if (isWheelSpun_) {
      if (!isHexSelected_) {
        trySelectActor(spunActorType_, coordinates);
        // if select success
        if (selectedActorId_ != -1) {
          selectedHexCoordinates_ = coordinates;
          isHexSelected_ = true;
        }
      } else {
        if (gameRunner_->checkActorMovement(selectedHexCoordinates_,
                                            coordinates, selectedActorId_,
                                            spunActorMoves_)) {
          gameRunner_->moveActor(selectedHexCoordinates_, coordinates,
                                 selectedActorId_, spunActorMoves_);
          gameState_->changeGamePhase(Common::GamePhase::MOVEMENT);
        }
      }
    }
    // TODO: Maybe have to print information for player if wheel hasn't spun.
    // Example "Spin wheel before trying to move actor"
  }
}

void GameExecuter::handleSpin() { isWheelSpun_ = true; }

} // namespace Student
