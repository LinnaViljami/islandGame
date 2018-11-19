#ifndef GAMEEXECUTER_HH
#define GAMEEXECUTER_HH

#include <QObject>
#include "igamerunner.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "cubecoordinate.hh"
#include "spinnercontainerwidget.hh"

namespace Student {

class GameExecuter : public QObject
{
        Q_OBJECT
public:
    GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner, std::shared_ptr<Student::GameBoard> gameBoard,
                 std::shared_ptr<Student::GameState> gameState, std::shared_ptr<SpinnerContainerWidget> spinnerWidget);
private:
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    std::shared_ptr<Student::GameBoard> gameBoard_;

    std::shared_ptr<Student::GameState> gameState_;

    std::shared_ptr<SpinnerContainerWidget> spinnerWidget_;

    Common::CubeCoordinate selectedHexCoordinates_;

    bool isHexSelected_;

    bool isWheelSpun_;

    std::string spunActorType_;
    int selectedActorId_;

    std::string spunActorMoves_;

    bool isPlayerPawnsInHex(Common::CubeCoordinate coord);

    std::vector<std::shared_ptr<Common::Pawn>>
    getPlayerPawnsInCoordinate(Common::CubeCoordinate coord);


    //Set new id to attribute "selectedActorId_", if "coord" have type "actorType" actor, else set -1;
    void trySelectActor(std::string actorType, Common::CubeCoordinate coord);

    void gamePhaseToSpinning();

    void tryMovePawn(Common::CubeCoordinate to);
public slots:
    void handleHexClick(Common::CubeCoordinate coordinates);
    void handleSpin();
};
}

#endif // GAMEEXECUTER_HH
