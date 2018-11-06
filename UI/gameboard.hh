#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "gameboardwidget.hh"
#include "igameboard.hh"
#include <map>

namespace Student {

class GameBoard : public Common::IGameBoard {

public:
  explicit GameBoard(Student::GameBoardWidget *boardWidget);

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
   * @copydoc IGameBoard::movePawn()
   */
  void movePawn(int pawnId, Common::CubeCoordinate pawnCoord) override;

  /**
   * @copydoc IGameBoard::removePawn()
   */
  void removePawn(int pawnId) override;

  /**
   * @copydoc IGameBoard::moveActor()
   */
  void moveActor(int actorId, Common::CubeCoordinate actorCoord) override;

  /**
   * @copydoc IGameBoard::removeActor()
   */
  void removeActor(int actorId) override;

private:
  Student::GameBoardWidget *_boardWidget;

  std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> _hexMap;

  std::map<int, std::shared_ptr<Common::Pawn>> _pawnsByIds;

  std::map<int, std::shared_ptr<Common::Actor>> _actorsByIds;
};

} // namespace Student
#endif // GAMEBOARD_HH
