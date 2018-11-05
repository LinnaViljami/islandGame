#include "gamewindow.hh"
#include "gameboard.hh"
#include "gameboardwidget.hh"
#include "gamestate.hh"
#include "hexgraphicsitem.hh"
#include "initialize.hh"
#include "player.hh"
#include "ui_gamewindow.h"

#include <qboxlayout.h>
#include <qlistview.h>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameWindow) {
  ui->setupUi(this);

  Student::GameBoardWidget *boardWidget = new Student::GameBoardWidget(this);

  auto gameBoard = std::make_shared<Student::GameBoard>(boardWidget);
  auto gameState = std::make_shared<Student::GameState>();

  boardWidget->setGameController(gameBoard);

  auto players = std::vector<shared_ptr<Common::IPlayer>>();
  for (int i = 0; i < 4; ++i) {
    auto player = std::make_shared<Student::Player>(i, 3);
    players.push_back(player);
  }

  auto gameRunner =
      Common::Initialization::getGameRunner(gameBoard, gameState, players);

  ui->centralwidget->setLayout(new QHBoxLayout());
  ui->centralwidget->layout()->addWidget(boardWidget);
}

GameWindow::~GameWindow() { delete ui; }
