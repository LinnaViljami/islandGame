#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include "gameexecuter.hh"
#include "player.hh"
#include "player.hh"

#include <QMainWindow>
#include <cubecoordinate.hh>
#include <igamerunner.hh>
#include <memory>

namespace Ui {

class GameWindow;
}

class GameWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit GameWindow(std::vector<QString> playerNames);
  ~GameWindow();

private:
  Ui::GameWindow *ui;
  std::unique_ptr<Student::GameExecuter> gameExecuter_;

  std::vector<std::shared_ptr<Student::Player>>
     createPlayers(std::vector<QString> names);
  std::vector<std::shared_ptr<Common::IPlayer>>
     castPlayersToIPlayers(std::vector<std::shared_ptr<Student::Player>> players);
};

#endif // GAMEWINDOW_HH
