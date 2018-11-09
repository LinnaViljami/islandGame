#include "gameexecuter.hh"
#include <QDebug>
#include <iostream>
#include "cubecoordinate.hh"

using Common::CubeCoordinate;
namespace Student {

GameExecuter::GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner,
                                    std::shared_ptr<Student::GameBoard> gameBoard,
                                    std::shared_ptr<Student::GameState> gameState) :
    _gameRunner(gameRunner), _gameBoard(gameBoard), _gameState(gameState)
{
    connect(_gameBoard->getBoardWidget().get(), &GameBoardWidget::hexClicked,
            this, &GameExecuter::handleHexClick);
}

void Student::GameExecuter::handleHexClick(Common::CubeCoordinate coordinates)
{
}
}
