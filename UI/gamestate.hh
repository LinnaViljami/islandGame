#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"
#include <vector>
using Common::GamePhase;

namespace Student {

class GameState : public Common::IGameState
{
public:
    GameState();
    ~GameState();    
    virtual GamePhase currentGamePhase() const = 0;
    virtual int currentPlayer() const = 0;
    virtual void changeGamePhase(Common::GamePhase nextPhase) = 0;
    virtual void changePlayerTurn(int nextPlayer) = 0;



private:
    GamePhase _gamePhase;
    int _playerInTurn;
    int _pawnsPerPlayer;
    std::vector<std::pair<int,int>> _playerPointVector;
    std::vector<std::pair<int,int>> _playerPawnVector;




    };



}

#endif // GAMESTATE_HH
