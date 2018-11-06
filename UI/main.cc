#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "startdialog.hh"

#include "gamewindow.hh"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

  StartDialog startDialog;
  int dialogResult = startDialog.exec();

  if (dialogResult != QDialog::Accepted) {
    return 0;
  } else {
    std::vector<QString> playerNames = startDialog.getPlayerNames();
    GameWindow mainWin(playerNames);
    mainWin.show();
    return a.exec();
  }
}
