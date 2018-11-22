#include "player.hh"
#include <vector>

namespace {
static const std::vector<Qt::GlobalColor> playerColors{
    Qt::GlobalColor::green, Qt::GlobalColor::blue, Qt::GlobalColor::red,
    Qt::GlobalColor::yellow};
}

namespace Student {

Player::Player(int id, unsigned int actionsLeft, QString name)
    : id_(id), actionsLeft_(actionsLeft), name_(name), points_(0) {}

int Player::getPlayerId() const { return id_; }

void Player::setActionsLeft(unsigned int actionsLeft) {
  actionsLeft_ = actionsLeft;
}

unsigned int Player::getActionsLeft() const { return actionsLeft_; }

QColor Player::getPlayerColor(int playerId) {
  return QColor(playerColors[playerId]);
}

QString Player::getName() const { return name_; }

void Player::setPoints(int points) { points_ = points; }

int Player::getPoints() const { return points_; }

} // namespace Student
