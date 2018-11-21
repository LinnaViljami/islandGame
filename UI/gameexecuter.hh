#ifndef GAMEEXECUTER_HH
#define GAMEEXECUTER_HH

#include "cubecoordinate.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "igamerunner.hh"
#include "spinnercontainerwidget.hh"
#include <QObject>
#include <iplayer.hh>
#include <vector>

namespace Student {

class GameExecuter : public QObject {
  Q_OBJECT
public:
  GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner,
               std::shared_ptr<Student::GameBoard> gameBoard,
               std::shared_ptr<Student::GameState> gameState,
               SpinnerContainerWidget *spinnerWidget,
               std::vector<std::shared_ptr<Common::IPlayer>> playerVector);

private:
  std::shared_ptr<Common::IGameRunner> gameRunner_;

  std::shared_ptr<Student::GameBoard> gameBoard_;

  std::shared_ptr<Student::GameState> gameState_;

  SpinnerContainerWidget *spinnerWidget_;

  std::vector<std::shared_ptr<Common::IPlayer>> playerVector_;

  Common::CubeCoordinate selectedHexCoordinates_;

  bool isHexSelected_;

  bool isWheelSpun_;

  int selectedActorId_;

  std::string spunActorMoves_;

  std::string spunActorType_;

  void handlePhaseMovement(Common::CubeCoordinate coord);

  void handlePhaseSinking(Common::CubeCoordinate coord);

  void handlePhaseSpinning(Common::CubeCoordinate coord);

  bool isPlayerPawnsInHex(Common::CubeCoordinate coord);

  std::vector<std::shared_ptr<Common::Pawn>>
  getPlayerPawnsInCoordinate(Common::CubeCoordinate coord);

  // Set new id to attribute "selectedActorId_", if "coord" have type
  // "actorType" actor, else set -1;
  bool trySelectActor(std::string actorType, Common::CubeCoordinate coord);

  bool trySelectTransport(std::string type, Common::CubeCoordinate coord);

  bool tryMoveActor(Common::CubeCoordinate to);

  bool tryMoveTransport(Common::CubeCoordinate to);

  bool tryFlipTile(Common::CubeCoordinate coord);

  bool tryDoActor(std::string type, Common::CubeCoordinate coord);

  void gamePhaseToMovement();

  //return true if hex has transport of type param "type"
  bool putPawnsToTransport(std::string type, Common::CubeCoordinate coord);

  void gamePhaseToSpinning();

  std::shared_ptr<Common::IPlayer> getCurrentPlayer();

  void tryMovePawn(Common::CubeCoordinate to);
public slots:
  void handleHexClick(Common::CubeCoordinate coordinates);

  void handleSpin();
};
} // namespace Student

#endif // GAMEEXECUTER_HH
