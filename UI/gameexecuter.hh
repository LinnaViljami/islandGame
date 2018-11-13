#ifndef GAMEEXECUTER_HH
#define GAMEEXECUTER_HH

#include <QObject>
#include "igamerunner.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "cubecoordinate.hh"

namespace Student {

class GameExecuter : public QObject
{
        Q_OBJECT
public:
    GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<Student::GameBoard> gameBoard, std::shared_ptr<Student::GameState> gameState);
private:
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    std::shared_ptr<Student::GameBoard> gameBoard_;

    std::shared_ptr<Student::GameState> gameState_;

    Common::CubeCoordinate selectedHexCoordinates_;

    bool isHexSelected_;



public slots:
    void handleHexClick(Common::CubeCoordinate coordinates);
};
}

#endif // GAMEEXECUTER_HH
