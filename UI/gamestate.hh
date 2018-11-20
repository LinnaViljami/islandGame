#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include <vector>
#include "../GameLogic/Engine/igamestate.hh"
#include <QObject>

namespace Student {

class GameState : public Common::IGameState
{

public:
    GameState();
    virtual Common::GamePhase currentGamePhase() const ;
    virtual int currentPlayer() const ;
    virtual void changeGamePhase(Common::GamePhase nextPhase);
    virtual void changePlayerTurn(int nextPlayer);
private:
    Common::GamePhase gamePhase_;
    int idOfPlayerInTurn_;
};
}

#endif // GAMESTATE_HH
