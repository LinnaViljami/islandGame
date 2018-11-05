#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "gameboardwidget.hh"
#include "igameboard.hh"
#include <map>
#include "igamecontroller.hh"

using Common::Actor;
using Common::CubeCoordinate;
using Common::Hex;
using Common::IGameBoard;
using Common::Pawn;
using std::map;
using std::shared_ptr;
using Student::GameBoardWidget;

namespace Student {

class GameBoard : public Common::IGameBoard, public Student::IGameController {

public:
  GameBoard(GameBoardWidget *boardWidget);

  /**
   * @copydoc IGameBoard::checkTileOccupation()
   */
  virtual int checkTileOccupation(CubeCoordinate tileCoord) const;

  /**
   * @copydoc IGameBoard::isWaterTile()
   */
  virtual bool isWaterTile(CubeCoordinate tileCoord) const;

  /**
   * @copydoc IGameBoard::getHex()
   */
  virtual shared_ptr<Hex> getHex(CubeCoordinate hexCoord) const;

  /**
   * @copydoc IGameBoard::addHex()
   */
  virtual void addHex(shared_ptr<Hex> newHex);

  /**
   * @copydoc IGameBoard::addPawn()
   */
  virtual void addPawn(int playerId, int pawnId);

  /**
   * @copydoc IGameBoard::movePawn()
   */
  virtual void movePawn(int pawnId, CubeCoordinate pawnCoord);

  /**
   * @copydoc IGameBoard::removePawn()
   */
  virtual void removePawn(int pawnId);

  /**
   * @copydoc IGameBoard::moveActor()
   */
  virtual void moveActor(int actorId, CubeCoordinate actorCoord);

  /**
   * @copydoc IGameBoard::removeActor()
   */
  virtual void removeActor(int actorId);

  void handleHexagonClick(Common::CubeCoordinate hexCoordinates);

private:
  GameBoardWidget *_boardWidget;

  map<CubeCoordinate, shared_ptr<Hex>> _hexMap;

  map<int, shared_ptr<Pawn>> _pawnsByIds;

  map<int, shared_ptr<Actor>> _actorsByIds;
};
} // namespace Student
#endif // GAMEBOARD_HH
