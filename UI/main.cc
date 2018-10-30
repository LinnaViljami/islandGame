#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"

#include <memory>
#include <QApplication>
#include "gamewindow.hh"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    GameWindow mainWin;
    mainWin.show();
    mainWin.init();
    return a.exec();
}
