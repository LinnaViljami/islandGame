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
#include <QLabel>
#include "userguidewidget.hh"

namespace Student {

class GameExecuter : public QObject {
  Q_OBJECT
public:
  GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner,
               std::shared_ptr<Student::GameBoard> gameBoard,
               std::shared_ptr<Student::GameState> gameState,
               SpinnerContainerWidget *spinnerWidget,
               std::vector<std::shared_ptr<Common::IPlayer>> playerVector,
               Student::UserGuideWidget* userGuide);

private:
  std::shared_ptr<Common::IGameRunner> gameRunner_;

  std::shared_ptr<Student::GameBoard> gameBoard_;

  std::shared_ptr<Student::GameState> gameState_;

  SpinnerContainerWidget *spinnerWidget_;

  std::vector<std::shared_ptr<Common::IPlayer>> playerVector_;

  Student::UserGuideWidget* userGuide_;

  Common::CubeCoordinate selectedHexCoordinates_;

  bool isHexSelected_;

  bool isWheelSpun_;

  int selectedActorId_;

  std::string movesOfSpunActor_;

  std::string typeOfSpunActor_;

  void handlePhaseMovement(Common::CubeCoordinate coord);

  void handlePhaseSinking(Common::CubeCoordinate coord);

  void handlePhaseSpinning(Common::CubeCoordinate coord);


  // Set new id to attribute "selectedActorId_", if "coord" have type
  // "actorType" actor, else set -1;
  bool trySelectActor(std::string actorType, Common::CubeCoordinate coord);

  bool trySelectTransport(std::string type, Common::CubeCoordinate coord);

  bool tryMoveActor(Common::CubeCoordinate to);

  bool tryMoveTransport(Common::CubeCoordinate to);

  bool tryFlipTile(Common::CubeCoordinate coord);

  bool tryDoActor(std::string type, Common::CubeCoordinate coord);

  void gamePhaseToMovement();

  void gamePhaseToSpinning();

  void tryMovePawn(Common::CubeCoordinate to);

  bool putPawnsToTransport(std::string type, Common::CubeCoordinate coord);

  std::vector<std::shared_ptr<Common::Pawn>>
  getPlayerPawnsInCoordinate(Common::CubeCoordinate coord);

  std::shared_ptr<Common::IPlayer> getCurrentPlayer();

  bool isPlayerPawnsInHex(Common::CubeCoordinate coord);

  void nextTurn();



public slots:
  void handleHexClick(Common::CubeCoordinate coordinates);

  void handleSpin();
};
} // namespace Student

#endif // GAMEEXECUTER_HH
