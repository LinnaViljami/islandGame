#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"

#include "gamewindow.hh"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  GameWindow mainWin;
  mainWin.show();
  return a.exec();
}
