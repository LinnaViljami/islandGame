#include "playerpointswidget.hh"

#include <QVBoxLayout>

using Student::Player;

namespace Student {

PlayerPointsWidget::PlayerPointsWidget(
    QWidget *parent, std::vector<std::shared_ptr<Player>> players)
    : QWidget(parent) {

  QVBoxLayout *layout = new QVBoxLayout(this);
  this->setLayout(layout);
  layout->setAlignment(Qt::AlignTop);

  auto *titleLabel = new QLabel("Pisteet:");
  layout->addWidget(titleLabel);

  for (std::shared_ptr<Player> player : players) {
    auto label = new QLabel();
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    QColor playerColor = Player::getPlayerColor(player->getPlayerId());
    label->setStyleSheet("color:" + playerColor.name());
    playerTextsByPlayers_[player] = label;
    layout->addWidget(label);
  }
  refreshPoints();
}

void PlayerPointsWidget::refreshPoints() {
  for (auto &&pair : playerTextsByPlayers_) {
    std::shared_ptr<Player> player = pair.first;
    QLabel *label = pair.second;
    label->setText(player->getName() + " : " + QString::number(player->getPoints()));
  }
}

} // namespace Student
