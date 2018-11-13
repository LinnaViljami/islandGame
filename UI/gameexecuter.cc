#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>


namespace Student {


GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState) :
    gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState), selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false)
{

    connect(gameBoard_->getBoardWidget(), &GameBoardWidget::hexClicked,
            this, &GameExecuter::handleHexClick);
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{
    qDebug() << "GameExecuter: Hex click detected at coordinate " << coordinates.x;


    if(gameState_->currentGamePhase() == Common::GamePhase::MOVEMENT){
        //if hex not selected
        if(not isHexSelected_){
            if(gameState_->currentPlayer())//if pawns in hex
            //select pressed hex
            selectedHexCoordinates_ = coordinates;
            //else error: not pawns in selected hex
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
