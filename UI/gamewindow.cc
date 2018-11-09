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

using Common::IPlayer;
using std::shared_ptr;
using std::vector;

namespace {

static const vector<QString> actors{QString("Dolphin"),    QString("Kraken"),
                                    QString("Seamonster"), QString("Shark"),
                                    QString("Boat"),       QString("Vortex")};

} // namespace

GameWindow::GameWindow(vector<QString> playerNames)
    : QMainWindow(nullptr), ui(new Ui::GameWindow) {
  ui->setupUi(this);

  auto boardWidget = new Student::GameBoardWidget(this);

  auto gameBoard = std::make_shared<Student::GameBoard>(boardWidget);
  auto gameState = std::make_shared<Student::GameState>();
  vector<shared_ptr<IPlayer>> players = createPlayers(playerNames);
  auto gameRunner = Common::Initialization::getGameRunner(gameBoard, gameState, players);
  auto gameExecuter = std::make_shared<Student::GameExecuter>(gameRunner, gameBoard, gameState);
  gameExecuter_ = gameExecuter;
  ui->mainLayout->addWidget(boardWidget);
  auto spinnerContainerWidget = new SpinnerContainerWidget(this, actors);
  spinnerContainerWidget->setMinimumSize(400, 400);
  ui->mainLayout->addWidget(spinnerContainerWidget);
  ui->mainLayout->setAlignment(spinnerContainerWidget, Qt::AlignTop);

  QPushButton *spinButton = new QPushButton("Pyöräytä");
  connect(spinButton, &QPushButton::clicked, this, [=]() {
    int actorIndex = std::rand() % actors.size();
    QString value = actors[actorIndex];
    spinnerContainerWidget->spinToValue(value);
  });
  ui->mainLayout->addWidget(spinButton);
  ui->mainLayout->setAlignment(spinButton, Qt::AlignHCenter);
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
