#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "gameboardwidget.hh"
#include "gamestate.hh"
#include "igameboard.hh"
#include "player.hh"
#include <QObject>
#include <iplayer.hh>
#include <map>
#include <vector>

namespace Student {

///
/// \brief GameBoard-class is store for all the hexes, paws, actors and the trasports
/// of the game. It also has some handy query-methods for different items.
///
class GameBoard : public QObject, public Common::IGameBoard {
  Q_OBJECT

public:
  explicit GameBoard(GameBoardWidget *boardWidget = nullptr);

  /**
   * @copydoc IGameBoard::checkTileOccupation()
   */
  int checkTileOccupation(Common::CubeCoordinate tileCoord) const override;

  /**
   * @copydoc IGameBoard::isWaterTile()
   */
  bool isWaterTile(Common::CubeCoordinate tileCoord) const override;

  /**
   * @copydoc IGameBoard::getHex()
   */
  std::shared_ptr<Common::Hex>
  getHex(Common::CubeCoordinate hexCoord) const override;

  /**
   * @copydoc IGameBoard::addHex()
   */
  void addHex(std::shared_ptr<Common::Hex> newHex) override;

  /**
   * @copydoc IGameBoard::addPawn()
   */
  void addPawn(int playerId, int pawnId) override;

  /**
   * @copydoc IGameBoard::addPawn()
   */
  virtual void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord);

  /**
   * @copydoc IGameBoard::movePawn()
   */
  void movePawn(int pawnId, Common::CubeCoordinate pawnCoord) override;

  /**
   * @copydoc IGameBoard::removePawn()
   */
  void removePawn(int pawnId) override;

  /**
   * @copydoc IGameBoard::addActor()
   */
  void addActor(std::shared_ptr<Common::Actor> actor,
                Common::CubeCoordinate actorCoord) override;

  /**
   * @copydoc IGameBoard::moveActor()
   */
  void moveActor(int actorId, Common::CubeCoordinate actorCoord) override;

  /**
   * @copydoc IGameBoard::removeActor()
   */
  void removeActor(int actorId) override;

  /**
   * @copydoc IGameBoard::addTransport()
   */
  void addTransport(std::shared_ptr<Common::Transport> transport,
                    Common::CubeCoordinate coord) override;

  /**
   * @copydoc IGameBoard::moveTransport()
   */
  void moveTransport(int id, Common::CubeCoordinate coord) override;

  /**
   * @copydoc IGameBoard::removeTransport()
   */
  void removeTransport(int id) override;

  ///
  /// \brief Returns true, if there is any piece of \p type.
  /// Otherwise returns false.
  ///
  bool isAnyPiecesOfType(std::string type) const;

  ///
  /// \brief Returns true, if there is any actor or transport of \p type.
  /// Otherwise returns false.
  ///
  bool isAnyActorsOrTransportsOfType(std::string type) const;

  ///
  /// \brief Returns true, if the game has ended, i.e all sinkable pieces has sunk.
  ///
  bool hasGameEnded() const;

  ///
  /// \brief Adds pawns to each player.
  /// \param players Players of the game.
  ///
  void initializePawns(std::vector<std::shared_ptr<Student::Player> > players);

  ///
  /// \brief Redraws the board according to current state of pieces, pawns etc.
  ///
  void updateBoard();

  ///
  /// \brief Returns all actors.
  ///
  std::vector<std::shared_ptr<Common::Actor>> getAllActors() const;

  ///
  /// \brief Returns amount of pawns of player.
  /// \param playerId The id of the player
  ///
  int getPlayerPawnAmount(int playerId);

private:
  Student::GameBoardWidget *boardWidget_;

  std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexMap_;

  std::map<int, std::shared_ptr<Common::Pawn>> pawnsByIds_;

  std::map<int, std::shared_ptr<Common::Actor>> actorsByIds_;

  std::map<int, std::shared_ptr<Common::Transport>> transportsByIds_;

  std::vector<std::shared_ptr<Common::Hex>> getAllHexes() const;
};

} // namespace Student
#endif // GAMEBOARD_HH
