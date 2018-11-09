#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>


namespace Student {


GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState) :
    _gameRunner(gameRunner), _gameBoard(gameBoard), _gameState(gameState)
{

    connect(_gameBoard->getBoardWidget(), &GameBoardWidget::hexClicked,
            this, &GameExecuter::handleHexClick);
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{
    qDebug() << "GameExecuter: Hex click detected at coordinate " << coordinates.x;
    //if(GameState)
    //if movement
        //if hex not already selected or not pawns to clicked hex
            // select/unselect hex
        //else
            //if pawn can move to clicked hex
                //move pawn
            //else
                //pawn cant move to clicked hex
    //if sinking
        //if clikced hex can sink
            //sink hex
            //play actor
            //handle pawn changes
        //else
            //hex cannot sink
    //if spinning
        //if actor can move to clicked hex
            //move actor
        //else
            //actor can not move to clicked hex
}

}
