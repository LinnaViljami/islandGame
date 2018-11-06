#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"
#include <QString>

namespace Student {

class Player : public Common::IPlayer {

public:
  Player(int id, unsigned int actionsLeft, QString name);

  virtual int getPlayerId() const;

  virtual void setActionsLeft(unsigned int actionsLeft);

  virtual unsigned int getActionsLeft() const;

  QString getName();

private:
  int _id;

  unsigned int _actionsLeft;

  QString _name;
};

} // namespace Student

#endif // PLAYER_HH
