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
    qDebug() << coordinates.x;
}

}
