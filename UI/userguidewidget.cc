#include "userguidewidget.hh"
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>

namespace Student {

UserGuideWidget::UserGuideWidget(QWidget *parent) : QWidget(parent) {
  this->setLayout(new QVBoxLayout(this));
  playerInTurnText_ = new QLabel("Default player in turn");
  doNextGuideText_ = new QLabel("Default guide to player");
  requestToUserText_ = new QLabel("Default request to player");

  this->layout()->addWidget(playerInTurnText_);
  this->layout()->addWidget(doNextGuideText_);
  this->layout()->addWidget(requestToUserText_);
}

void UserGuideWidget::setPlayerInTurn(std::shared_ptr<Player> playerInTurn) {
  playerInTurnText_->setText("Vuorossa " + playerInTurn->getName());
  QColor playerColor = Player::getPlayerColor(playerInTurn->getPlayerId());
  playerInTurnText_->setStyleSheet("color:" + playerColor.name());
}

void UserGuideWidget::setGuide(QString) {}

void UserGuideWidget::setRequestToUser(QString) {}

} // namespace Student
