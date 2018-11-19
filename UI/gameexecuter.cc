#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>
#include "gameexception.hh"
#include <vector>
#include "actor.hh"


namespace Student {


GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<GameBoard> gameBoard,
                           std::shared_ptr<GameState> gameState, std::shared_ptr<SpinnerContainerWidget> spinnerWidget) :
    gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState), spinnerWidget_(spinnerWidget), selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false),
    isWheelSpun_(false), selectedActorId_(-1), selectedActorMoves_(std::string())
{

    connect(gameBoard_->getBoardWidget(), &GameBoardWidget::hexClicked,
            this, &GameExecuter::handleHexClick);
    gameState->changePlayerTurn(1);
    gameState->changeGamePhase(Common::GamePhase::MOVEMENT);
}

bool GameExecuter::isPlayerPawnsInHex(Common::CubeCoordinate coord)
{
    std::vector<std::shared_ptr<Common::Pawn>> playerPawns = getPlayerPawnsInCoordinate(coord);
    return (playerPawns.size()!=0);

}

std::vector<std::shared_ptr<Common::Pawn> > GameExecuter::getPlayerPawnsInCoordinate(Common::CubeCoordinate coord)
{
    std::vector<std::shared_ptr<Common::Pawn>> pawnsInClickedHex = gameBoard_->getHex(coord)->getPawns();
    std::vector<std::shared_ptr<Common::Pawn>> playerPawns;
    for(auto const& pawn : pawnsInClickedHex){
        if(pawn->getPlayerId() == gameState_->currentPlayer()){
            playerPawns.push_back(pawn);
        }
    }
    return playerPawns;
}

void GameExecuter::tryMovePawn(Common::CubeCoordinate to)
{
    //take all current player pawns and try to move them one by one.
    //if move succes, unselect selected hex, update moves left and move pawn.
    std::vector<std::shared_ptr<Common::Pawn>> playerPawnsInSelected = getPlayerPawnsInCoordinate(selectedHexCoordinates_);
    if(playerPawnsInSelected.size()!=0){
        for(auto const& pawn : playerPawnsInSelected){
            int movesLeft = gameRunner_->checkPawnMovement(selectedHexCoordinates_, to, pawn->getId());
            if(movesLeft>=0){
                gameRunner_->movePawn(selectedHexCoordinates_,to,pawn->getId());
                gameState_->setMovesLeft(movesLeft);
                isHexSelected_ = false;
                return;
            }
        }
    }
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{

    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coordinates);
    if(gameState_->currentGamePhase() == Common::GamePhase::MOVEMENT){
        //if no moves left go to sinking
        if(gameState_->getMovesLeft()<=0){
            gameState_->changeGamePhase(Common::GamePhase::SINKING);
            isHexSelected_ = false;
        }
        else if(clickedHex == nullptr){
            throw Common::GameException("Clicked hex not exist in game-executer gameboard_");
        }
        else if(!isHexSelected_){
            //TODO: if pawns in transports
            if(isPlayerPawnsInHex(coordinates)){
                selectedHexCoordinates_ = coordinates;
                isHexSelected_ = true;
            }
            else{
                qDebug() << "Cannot select clicked hex because you dont have pawns in it";
            }
        }
        //if hex is selected
        else if(isHexSelected_){
            if(selectedHexCoordinates_.operator ==(coordinates)){
                //unselect hex
                isHexSelected_ = false;
            }
            else{
                //tryToMovePawn
                //TODO: Move transport to transport
                tryMovePawn(coordinates);
            }
        }

    }
    else if(gameState_->currentGamePhase() == Common::GamePhase::SINKING){
        std::string actor = gameRunner_->flipTile(coordinates);
        //if flip success
        if(!actor.empty()){
            //find right factor to hex
            for(auto const& a : clickedHex->getActors()){
                if(a->getActorType()==actor){
                    a->doAction();
                    //TODO: Maybe should handle pawn changes?
                    //Actor::doaction(); not implemented yet so I am not sure what should do...
                    gameState_->changeGamePhase(Common::GamePhase::SPINNING);
                    gameRunner_->spinWheel();
                    isHexSelected_ = false;
                    return;
                }
            }
        }
    }
    else if(gameState_->currentGamePhase() == Common::GamePhase::SPINNING){
        if(isWheelSpun_){
            if(!isHexSelected_){
                selectedHexCoordinates_ = coordinates;
                isHexSelected_ = true;
            }
            else{
                if(gameRunner_->checkActorMovement(selectedHexCoordinates_, coordinates, selectedActorId_, selectedActorMoves_)){
                    gameRunner_->moveActor(selectedHexCoordinates_, coordinates, selectedActorId_, selectedActorMoves_);
                    gameState_->changeGamePhase(Common::GamePhase::MOVEMENT);
                }
            }
        }
        //TODO: Maybe have to print information for player if wheel hasn't spun.
        //Example "Spin wheel before trying to move actor"
    }

}

}
