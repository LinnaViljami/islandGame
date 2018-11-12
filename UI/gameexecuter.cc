#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>


namespace Student {


GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState) :
    _gameRunner(gameRunner), _gameBoard(gameBoard), _gameState(gameState), _selectedHexCoordinates(Common::CubeCoordinate())
{

    connect(_gameBoard->getBoardWidget(), &GameBoardWidget::hexClicked,
            this, &GameExecuter::handleHexClick);
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{
    qDebug() << "GameExecuter: Hex click detected at coordinate " << coordinates.x;


    if(_gameState->currentGamePhase() == Common::GamePhase::MOVEMENT){
        //if hex not selected
        if(_selectedHexCoordinates == Common::CubeCoordinate()){
            if(_gameState->currentPlayer())//if pawns in hex
            //select pressed hex
            _selectedHexCoordinates = coordinates;
            //else error: not pawns in selected hex
        }
        else if(_selectedHexCoordinates.operator ==(coordinates)){
            //unselect hex
            _selectedHexCoordinates = Common::CubeCoordinate();
        }
        else{
            //if able to move pawns -> move
            //else error: not able to move
        }
    }
    else if(_gameState->currentGamePhase() == Common::GamePhase::SINKING){
        //if clikced hex can sink
            //sink hex
            //play actor
            //handle pawn changes
        //else
            //hex cannot sink
    }
    else if(_gameState->currentGamePhase() == Common::GamePhase::SPINNING){
        //if player has spin the wheel
            //if actor can move to clicked hex
                //move actor
            //else
                //actor can not move to clicked hex
        //else: ERROR cannot move actor before wheel spin
    }

}

}
