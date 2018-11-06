#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include "player.hh"
#include <QMainWindow>
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

  std::vector<std::shared_ptr<Common::IPlayer>>
  createPlayers(std::vector<QString> names);
};

#endif // GAMEWINDOW_HH
