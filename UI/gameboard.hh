#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "gameboardwidget.hh"
#include "igameboard.hh"
#include <map>

namespace Student {

class GameBoard : public Common::IGameBoard {

public:
  GameBoard(Student::GameBoardWidget *boardWidget);

  /**
   * @copydoc IGameBoard::checkTileOccupation()
   */
  virtual int checkTileOccupation(Common::CubeCoordinate tileCoord) const;

  /**
   * @copydoc IGameBoard::isWaterTile()
   */
  virtual bool isWaterTile(Common::CubeCoordinate tileCoord) const;

  /**
   * @copydoc IGameBoard::getHex()
   */
  virtual std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;

  /**
   * @copydoc IGameBoard::addHex()
   */
  virtual void addHex(std::shared_ptr<Common::Hex> newHex);

  /**
   * @copydoc IGameBoard::addPawn()
   */
  virtual void addPawn(int playerId, int pawnId);

  /**
   * @copydoc IGameBoard::movePawn()
   */
  virtual void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);

  /**
   * @copydoc IGameBoard::removePawn()
   */
  virtual void removePawn(int pawnId);

  /**
   * @copydoc IGameBoard::moveActor()
   */
  virtual void moveActor(int actorId, Common::CubeCoordinate actorCoord);


  /**
   * @copydoc IGameBoard::removeActor()
   */
  virtual void removeActor(int actorId);

private:
  Student::GameBoardWidget *_boardWidget;

  std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> _hexMap;

  std::map<int, std::shared_ptr<Common::Pawn>> _pawnsByIds;

  std::map<int, std::shared_ptr<Common::Actor>> _actorsByIds;
};

} // namespace Student
#endif // GAMEBOARD_HH
