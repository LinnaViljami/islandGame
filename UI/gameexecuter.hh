#ifndef GAMEEXECUTER_HH
#define GAMEEXECUTER_HH

#include "cubecoordinate.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "igamerunner.hh"
#include "player.hh"
#include "playerpointswidget.hh"
#include "spinnercontainerwidget.hh"
#include "userguidewidget.hh"
#include <QLabel>
#include <QObject>
#include <player.hh>
#include <vector>

/**
 * @file
 * @brief Contains class GameExecuter header.
 *
 *  It handle UI events and command GameÉngine to update its attributes.
 */
namespace Student {

/**
 * @brief The GameExecuter class synchronizes UI and GameEngine together.
 */
class GameExecuter : public QObject {
  Q_OBJECT
public:

    /**
     * @brief Constructor
     */
  GameExecuter(std::shared_ptr<Common::IGameRunner> gameRunner,
               std::shared_ptr<Student::GameBoard> gameBoard,
               std::shared_ptr<Student::GameState> gameState,
               SpinnerContainerWidget *spinnerWidget,
               GameBoardWidget *gameBoardWidget,
               std::vector<std::shared_ptr<Student::Player>> playerVector,
               Student::UserGuideWidget *userGuide,
               Student::PlayerPointsWidget *playerPointsWidget);

public slots:
  /**
   * @brief Command executer to handle turn skipping
   */
  void skipCurrentPhaseRequested();

private:

  /**
   * @defgroup Game components
   * @{
   */
  std::shared_ptr<Common::IGameRunner> gameRunner_;
  std::shared_ptr<Student::GameBoard> gameBoard_;
  std::shared_ptr<Student::GameState> gameState_;
  SpinnerContainerWidget *spinnerWidget_;
  GameBoardWidget *gameBoardWidget_;
  std::vector<std::shared_ptr<Student::Player>> playerVector_;
  Student::UserGuideWidget *userGuide_;
  Student::PlayerPointsWidget *playerPointsWidget_;
  /** @} */

  /**
   * @defgroup Game flow variables
   * @{
   */
  Common::CubeCoordinate selectedHexCoordinates_;
  bool isHexSelected_;
  bool isWheelSpun_;
  bool hasGameEnded_;
  int selectedActorId_;
  std::string movesOfSpunActor_;
  std::string typeOfSpunActor_;
  /** @} */

  /**
   * @defgroup Game flow handlers
   * @{
   */
  void handlePhaseMovement(Common::CubeCoordinate coord);
  void handlePhaseSinking(Common::CubeCoordinate coord);
  void handlePhaseSpinning(Common::CubeCoordinate coord);
  /** @} */

  /**
   * @defgroup Selectors
   * @{
   * @brief Try to select array in given coordinates.
   * @param type Type of array to select.
   * @param coord Coordinate of array.
   * @return true if select success. False if not.
   */
  bool trySelectActor(std::string type, Common::CubeCoordinate coord);
  bool trySelectTransport(std::string type, Common::CubeCoordinate coord);
  /** @} */

  /**
   * @defgroup Move functions
   * @{
   * @brief Try move arrays to new coordinate.
   * @param to New coordinate of array.
   * @return true if moving succes. False if not.
   */
  bool tryMoveActor(Common::CubeCoordinate to);
  bool tryMoveTransport(Common::CubeCoordinate to);
  bool tryMovePawn(Common::CubeCoordinate to);
  bool tryMoveTransportWithSpinner(Common::CubeCoordinate to, std::string moves);
  /** @} */


  /**
   * @brief tryFlipTile Flip tile if possible.
   * @param coord Coordinates of tile
   * @return True if flip succes. False if not.
   */
  bool tryFlipTile(Common::CubeCoordinate coord);

  /**
   * @brief tryDoActor Try to do actor if possible.
   * @param type Describe type of actor
   * @param coord Coordinates of actor.
   * @return True if actor can do it's action. False if actor can't do it's action
   */
  bool tryDoActor(std::string type, Common::CubeCoordinate coord);

  /**
   * @defgroup GamePhase changing functions
   * @{
   * @brief Do all what needs to do when GamePhase changes.
   */
  void gamePhaseToMovement();
  void gamePhaseToSinking();
  void gamePhaseToSpinning();
  /** @} */

  /**
   * @brief putPawnsToTransport Try to put all pawns of given coordinate to transport.
   * @param type Type of transport where pawns put.
   * @param coord Coordinates of transport and pawns
   * @return True if transport of given type exist in given coordinate.
   */
  bool putPawnsToTransport(std::string type, Common::CubeCoordinate coord);

  /**
   * @brief getPlayerPawnsInCoordinate Give current player all pawns in given coordinate.
   * @param coord Coordinate of pawns
   * @return Vector include shared pointers to pawns.
   */
  std::vector<std::shared_ptr<Common::Pawn>>
  getPlayerPawnsInCoordinate(Common::CubeCoordinate coord);

  std::shared_ptr<Student::Player> getCurrentPlayer();

  bool isPlayerPawnsInHex(Common::CubeCoordinate coord);

  std::shared_ptr<Student::Player> getPlayerWithMostPoints();

  /**
   * @brief nextTurn Give turn to next player.
   */
  void nextTurn();

  /**
   * @brief doActionsOfAllActors Try to do all actors which exist in gameboard.
   */
  void doActionsOfAllActors();

  /**
   * @brief updatePoints Update points of every player.
   * Command players to update point attribute and userGuideWidget to refresh UI.
   */
  void updatePoints();

  /**
   * @brief goToNextState Command game flow handler functions to flow next game state.
   */
  void goToNextState();

  /**
   * @brief handleGameEnding called if game has ended
   */
  void handleGameEnding();

private slots:
  /**
   * @brief handleHexClick Command clickHandler when user click hexagon.
   * @param coordinates Cliked hex coordinates
   */
  void handleHexClick(Common::CubeCoordinate coordinates);

  /**
   * @brief handleSpin Command spin handler functions when spinner began to spin.
   */
  void handleSpin();
};
} // namespace Student

#endif // GAMEEXECUTER_HH
