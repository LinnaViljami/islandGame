#include "gamewindow.hh"
#include "gameboard.hh"
#include "gameboardwidget.hh"
#include "gamestate.hh"
#include "hexgraphicsitem.hh"
#include "initialize.hh"
#include "player.hh"
#include "spinnerwidget.hh"
#include "startdialog.hh"
#include "ui_gamewindow.h"
#include "gamerunner.hh"

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

  auto gameRunner =
      Common::Initialization::getGameRunner(gameBoard, gameState, players);

  ui->mainLayout->addWidget(boardWidget);
  auto spinnerWidget = new SpinnerWidget(this, actors);
  spinnerWidget->setMinimumSize(400, 400);
  ui->mainLayout->addWidget(spinnerWidget);
  ui->mainLayout->setAlignment(spinnerWidget, Qt::AlignTop);
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
