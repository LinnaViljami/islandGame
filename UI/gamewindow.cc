#include "gamewindow.hh"
#include "gameboard.hh"
#include "gameboardwidget.hh"
#include "gamestate.hh"
#include "hexgraphicsitem.hh"
#include "initialize.hh"
#include "player.hh"
#include "spinnercontainerwidget.hh"
#include "startdialog.hh"
#include "ui_gamewindow.h"
#include <QPushButton>
#include <qboxlayout.h>
#include <qlistview.h>
#include <QLabel>

using Common::IPlayer;
using std::shared_ptr;
using std::vector;

GameWindow::GameWindow(vector<QString> playerNames)
    : QMainWindow(nullptr), ui(new Ui::GameWindow) {
  ui->setupUi(this);

  auto boardWidget = new Student::GameBoardWidget(this);

  auto gameBoard = std::make_shared<Student::GameBoard>(boardWidget);
  auto gameState = std::make_shared<Student::GameState>();
  vector<shared_ptr<IPlayer>> players = createPlayers(playerNames);
  auto gameRunner =
      Common::Initialization::getGameRunner(gameBoard, gameState, players);

  auto vLayout = new QVBoxLayout(this);
  auto userGuideText  = std::make_shared<QLabel>("Tervetuloa pelaamaan LoveIsland SUomi2018!");
  ui->mainLayout->addLayout(vLayout);
  vLayout->addWidget(userGuideText.get());
  vLayout->addWidget(boardWidget);

  SpinnerLayout spinnerLayout = gameRunner->getSpinnerLayout();
  auto spinnerContainerWidget = new SpinnerContainerWidget(this, spinnerLayout);
  spinnerContainerWidget->setMinimumSize(200, 400);
  ui->mainLayout->addWidget(spinnerContainerWidget);
  ui->mainLayout->setAlignment(spinnerContainerWidget, Qt::AlignTop);

  gameExecuter_ = std::make_unique<Student::GameExecuter>(
      gameRunner, gameBoard, gameState, spinnerContainerWidget, players, userGuideText);

  gameBoard->initializePawns(players);
  boardWidget->updateBoard();
}

GameWindow::~GameWindow() { delete ui; }

vector<shared_ptr<IPlayer>> GameWindow::createPlayers(vector<QString> names) {
  auto players = vector<shared_ptr<IPlayer>>();
  for (unsigned int i = 0; i < names.size(); ++i) {
    QString playerName = names[i];
    auto player = std::make_shared<Student::Player>(i, 3, playerName);
    players.push_back(player);
  }
  return players;
}
