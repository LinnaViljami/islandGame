#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "startdialog.hh"

#include "gamewindow.hh"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

  Student::StartDialog startDialog;
  int dialogResult = startDialog.exec();

  if (dialogResult != QDialog::Accepted) {
    return 0;
  } else {
    std::vector<QString> playerNames = startDialog.getPlayerNames();
    Student::GameWindow mainWin(playerNames);
    mainWin.showMaximized();
    return a.exec();
  }
}
