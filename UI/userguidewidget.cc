#include "userguidewidget.hh"
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>

namespace Student {

UserGuideWidget::UserGuideWidget(QWidget *parent) : QWidget(parent) {
  this->setLayout(new QVBoxLayout(this));
  playerInTurnText_ = new QLabel();
  nextActionGuideText_ = new QLabel();
  additionalMessageText_ = new QLabel();

  this->layout()->addWidget(playerInTurnText_);
  this->layout()->addWidget(nextActionGuideText_);
  this->layout()->addWidget(additionalMessageText_);
}

void UserGuideWidget::setPlayerInTurn(std::shared_ptr<Player> playerInTurn) {
  playerInTurnText_->setText("Vuorossa " + playerInTurn->getName());
  QColor playerColor = Player::getPlayerColor(playerInTurn->getPlayerId());
  playerInTurnText_->setStyleSheet("color:" + playerColor.name());
}

void UserGuideWidget::setNextActionGuide(QString message) {
    nextActionGuideText_->setText(message);
}

void UserGuideWidget::setAdditionalMessage(QString message) {
    additionalMessageText_->setText(message);
}

void UserGuideWidget::setWinnerPlayer(std::shared_ptr<Player> winner)
{
    playerInTurnText_->setText("Pelin voitti " + winner->getName());
    QColor winnerColor = Player::getPlayerColor(winner->getPlayerId());
    playerInTurnText_->setStyleSheet("color:" + winnerColor.name());
}
} // namespace Student
