#include "player.hh"

namespace Student {

Player::Player(int id, unsigned int actionsLeft, QString name)
    : id_(id), actionsLeft_(actionsLeft), name_(name) {}

int Player::getPlayerId() const { return id_; }

void Player::setActionsLeft(unsigned int actionsLeft) {
  actionsLeft_ = actionsLeft;
}

unsigned int Player::getActionsLeft() const { return actionsLeft_; }

QString Player::getName() { return name_; }

} // namespace Student
