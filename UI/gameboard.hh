#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "igameboard.hh"
#include <map>

using Common::CubeCoordinate;
using Common::Hex;
using Common::IGameBoard;
using Common::Pawn;
using std::map;
using std::shared_ptr;

namespace Student {

class GameBoard : public Common::IGameBoard {

public:
  GameBoard();

  ~GameBoard();

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

private:
  shared_ptr<Hex> getCenterHex() const;

  map<CubeCoordinate, shared_ptr<Hex>> _hexMap;

  map<int, shared_ptr<Pawn>> _pawnsByIds;
};

} // namespace Student
#endif // GAMEBOARD_HH
