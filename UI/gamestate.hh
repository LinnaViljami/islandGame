#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include <vector>
#include "../GameLogic/Engine/igamestate.hh"

using Common::GamePhase;

namespace Student {

class GameState : public Common::IGameState
{

public:
    GameState();
    virtual GamePhase currentGamePhase() const ;
    virtual int currentPlayer() const ;
    virtual void changeGamePhase(Common::GamePhase nextPhase);
    virtual void changePlayerTurn(int nextPlayer);

private:
    GamePhase _gamePhase;
    int _idOfPlayerInTurn;
};
}

#endif // GAMESTATE_HH
