#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "../GameLogic/Engine/igamestate.hh"
#include <QObject>
#include <vector>

namespace Student {

///
/// \brief Data class containing id of the current player
///  and the current game phase.
///
class GameState : public Common::IGameState {

public:
  GameState();

  /**
   * @copydoc IGameState::currentGamePhase()
   */
  virtual Common::GamePhase currentGamePhase() const;

  /**
   * @copydoc IGameState::currentPlayer()
   */
  virtual int currentPlayer() const;

  /**
   * @copydoc IGameState::changeGamePhase()
   */
  virtual void changeGamePhase(Common::GamePhase nextPhase);

  /**
   * @copydoc IGameState::changePlayerTurn()
   */
  virtual void changePlayerTurn(int nextPlayer);

private:
  Common::GamePhase gamePhase_;
  int idOfPlayerInTurn_;
};
} // namespace Student

#endif // GAMESTATE_HH
