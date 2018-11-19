#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>
#include "gameexception.hh"
#include <vector>
#include "actor.hh"


namespace Student {


GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState) :
    gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState), selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false),
    isWheelSpun_(false)
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
    std::vector<std::shared_ptr<Common::Pawn>> playerPawnsInSelected = getPlayerPawnsInCoordinate(selectedHexCoordinates_);
    if(playerPawnsInSelected.size()!=0){
        for(auto const& pawn : playerPawnsInSelected){
            int movesLeft = gameRunner_->checkPawnMovement(selectedHexCoordinates_, to, pawn->getId());
            if(movesLeft>=0){
                gameRunner_->movePawn(selectedHexCoordinates_,to,pawn->getId());
                gameState_->setMovesLeft(movesLeft);
                isHexSelected_ = false;
                break;
            }
        }
    }
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coordinates);
    if(gameState_->currentGamePhase() == Common::GamePhase::MOVEMENT){
        if(clickedHex == nullptr){
            throw Common::GameException("Clicked hex not exist in game-executer gameboard_");
        }
        else if(!isHexSelected_){
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
                tryMovePawn(coordinates);
            }
        }
        //if no moves left go to sinking
        if(gameState_->getMovesLeft()<=0){
            gameState_->changeGamePhase(Common::GamePhase::SINKING);
        }
    }

    else if(gameState_->currentGamePhase() == Common::GamePhase::SINKING){
//        if(!gameBoard_->isAnyPiecesOfType("Beach")){
//            gameState_->changeGamePhase(Common::GamePhase::SPINNING);
//        }
//        else if(clickedHex->getPieceType()=="Beach"){
            std::string actor = gameRunner_->flipTile(coordinates);
            if(!actor.empty()){
                for(auto const& a : clickedHex->getActors()){
                    if(a->getActorType()==actor){
                        a->doAction();
                        //handle pawn changes?
                    }
                }
            }
        }
   // }
    else if(gameState_->currentGamePhase() == Common::GamePhase::SPINNING){
        if(isWheelSpun_){
            //gameRunner_->checkActorMovement();
        }
        //if player has spin the wheel
            //if actor can move to clicked hex
                //move actor
            //else
                //actor can not move to clicked hex
        //else: ERROR cannot move actor before wheel spin
    }

}

}
