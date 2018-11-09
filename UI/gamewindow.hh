#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include "player.hh"
#include "gameexecuter.hh"

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

  std::vector<std::shared_ptr<Common::IPlayer>>
  createPlayers(std::vector<QString> names);
};

#endif // GAMEWINDOW_HH
