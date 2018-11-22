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

class GameBoard : public QObject, public Common::IGameBoard {
  Q_OBJECT

public:
  explicit GameBoard(GameBoardWidget *boardWidget = nullptr);

  GameBoardWidget *getBoardWidget();

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

  bool isAnyPiecesOfType(std::string type) const;

  bool isAnyActorsOrTransportsOfType(std::string type) const;

  bool hasGameEnded() const;

  void initializePawns(std::vector<std::shared_ptr<Student::Player> > players);

private:
  Student::GameBoardWidget *boardWidget_;

  std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexMap_;

  std::map<int, std::shared_ptr<Common::Pawn>> pawnsByIds_;

  std::map<int, std::shared_ptr<Common::Actor>> actorsByIds_;

  std::map<int, std::shared_ptr<Common::Transport>> transportsByIds_;
};

} // namespace Student
#endif // GAMEBOARD_HH
