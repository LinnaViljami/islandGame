#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>
#include "gameexception.hh"
#include <vector>


namespace Student {


GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState) :
    gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState), selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false)
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

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{
    if(gameState_->currentGamePhase() == Common::GamePhase::MOVEMENT){
         std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coordinates);

        if(clickedHex == nullptr){
            throw Common::GameException("Clicked hex not exist in game-executer gameboard_");
        }
        else if(!isHexSelected_){
            bool testi = isPlayerPawnsInHex(coordinates);
            //if player has pawns in selected hex
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
        }
        else if(selectedHexCoordinates_.operator ==(coordinates)){
            //unselect hex
            isHexSelected_ = true;
        }
        else{
            //if able to move pawns -> move
            //else error: not able to move
        }
    }
    else if(gameState_->currentGamePhase() == Common::GamePhase::SINKING){
        //if clikced hex can sink
            //sink hex
            //play actor
            //handle pawn changes
        //else
            //hex cannot sink
    }
    else if(gameState_->currentGamePhase() == Common::GamePhase::SPINNING){
        //if player has spin the wheel
            //if actor can move to clicked hex
                //move actor
            //else
                //actor can not move to clicked hex
        //else: ERROR cannot move actor before wheel spin
    }

}

}
