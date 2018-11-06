#include "player.hh"

namespace Student {

Player::Player(int id, unsigned int actionsLeft, QString name)
    : _id(id), _actionsLeft(actionsLeft), _name(name) {}

int Player::getPlayerId() const { return _id; }

void Player::setActionsLeft(unsigned int actionsLeft) {
  _actionsLeft = actionsLeft;
}

unsigned int Player::getActionsLeft() const { return _actionsLeft; }

QString Player::getName() { return _name; }

} // namespace Student
