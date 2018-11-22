#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"
#include <QColor>
#include <QString>
#include <QColor>

namespace Student {

class Player : public Common::IPlayer {

public:
  Player(int id, unsigned int actionsLeft, QString name);

  virtual int getPlayerId() const;

  virtual void setActionsLeft(unsigned int actionsLeft);

  virtual unsigned int getActionsLeft() const;

  QString getName() const;

  void setPoints(int points);

  int getPoints() const;

  static QColor getPlayerColor(int playerId);
private:
  int id_;

  unsigned int actionsLeft_;

  QString name_;

  int points_;
};

} // namespace Student

#endif // PLAYER_HH
