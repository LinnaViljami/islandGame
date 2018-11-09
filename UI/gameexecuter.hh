#ifndef GAMEEXECUTER_HH
#define GAMEEXECUTER_HH

#include <QObject>
#include "igamerunner.hh"
#include "gameboard.hh"
#include "gamestate.hh"

namespace Student {

class GameExecuter : public QObject
{
        Q_OBJECT
public:
    GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<Student::GameBoard> gameBoard, std::shared_ptr<Student::GameState> gameState);
private:
    std::shared_ptr<Common::IGameRunner> _gameRunner;

    std::shared_ptr<Student::GameBoard> _gameBoard;

    std::shared_ptr<Student::GameState> _gameState;

public slots:
    void handleHexClick(Common::CubeCoordinate coordinates);
};
}

#endif // GAMEEXECUTER_HH
