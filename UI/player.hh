#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

namespace Student {

class Player : public Common::IPlayer {

public:
  Player(int id, unsigned int actionsLeft);

  virtual int getPlayerId() const;

  virtual void setActionsLeft(unsigned int actionsLeft);

  virtual unsigned int getActionsLeft() const;

private:
  int _id;

  unsigned int _actionsLeft;
};

} // namespace Student

#endif // PLAYER_HH
