#include "gamewindow.hh"
#include "gameboard.hh"
#include "gameboardwidget.hh"
#include "gamestate.hh"
#include "hexgraphicsitem.hh"
#include "initialize.hh"
#include "player.hh"
#include "playerpointswidget.hh"
#include "spinnercontainerwidget.hh"
#include "startdialog.hh"
#include "ui_gamewindow.h"
#include "userguidewidget.hh"
#include <QPushButton>
#include <qboxlayout.h>
#include <qlistview.h>

using Common::IPlayer;
using std::shared_ptr;
using std::vector;
using Student::Player;

namespace Student {

GameWindow::GameWindow(vector<QString> playerNames)
    : QMainWindow(nullptr), ui(new Ui::GameWindow) {
  ui->setupUi(this);
  std::srand(std::time(0));

  auto boardWidget = new Student::GameBoardWidget(this);

  auto gameBoard = std::make_shared<Student::GameBoard>(boardWidget);
  auto gameState = std::make_shared<Student::GameState>();
  vector<shared_ptr<Player>> players = createPlayers(playerNames);
  auto gameRunner = Common::Initialization::getGameRunner(
      gameBoard, gameState, castPlayersToIPlayers(players));

  auto userGuideWidget = new Student::UserGuideWidget(this);
  ui->leftLayout->addWidget(userGuideWidget);
  ui->leftLayout->addWidget(boardWidget);
  ui->leftLayout->addWidget(ui->zoomingAndPanningGuideLabel);

  SpinnerLayout spinnerLayout = gameRunner->getSpinnerLayout();
  auto spinnerContainerWidget = new SpinnerContainerWidget(this, spinnerLayout);
  spinnerContainerWidget->setMinimumSize(200, 400);
  ui->rightLayout->addWidget(spinnerContainerWidget);
  ui->rightLayout->setAlignment(spinnerContainerWidget, Qt::AlignTop);

  auto pointsWidget = new Student::PlayerPointsWidget(this, players);
  ui->rightLayout->addWidget(pointsWidget);

  gameExecuter_ = std::make_unique<Student::GameExecuter>(
      gameRunner, gameBoard, gameState, spinnerContainerWidget, boardWidget,
      players, userGuideWidget, pointsWidget);

  gameBoard->initializePawns(players);
  boardWidget->updateBoard();
}

GameWindow::~GameWindow() { delete ui; }

vector<shared_ptr<Player>> GameWindow::createPlayers(vector<QString> names) {
  auto players = vector<shared_ptr<Player>>();
  for (unsigned int i = 0; i < names.size(); ++i) {
    QString playerName = names[i];
    auto player = std::make_shared<Player>(i, 3, playerName);
    players.push_back(player);
  }
  return players;
}

vector<shared_ptr<IPlayer>>
GameWindow::castPlayersToIPlayers(vector<shared_ptr<Player>> players) {
  auto iplayers = vector<shared_ptr<IPlayer>>();
  std::copy(players.begin(), players.end(), std::back_inserter(iplayers));
  return iplayers;
}

} // namespace Student
