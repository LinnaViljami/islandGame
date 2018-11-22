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

  static const QColor getPlayerColor(int playerId);

  QString getName();

private:
  int id_;

  unsigned int actionsLeft_;

  QString name_;
};

} // namespace Student

#endif // PLAYER_HH
