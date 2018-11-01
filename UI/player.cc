#include "player.hh"

namespace Student {

Player::Player(int id, unsigned int actionsLeft)
    : _id(id), _actionsLeft(actionsLeft) {}

int Player::getPlayerId() const { return _id; }

void Player::setActionsLeft(unsigned int actionsLeft) {
  _actionsLeft = actionsLeft;
}

unsigned int Player::getActionsLeft() const { return _actionsLeft; }

} // namespace Student
