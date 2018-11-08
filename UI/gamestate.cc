#include "gamestate.hh"

using Common::GamePhase;

namespace Student{

Student::GameState::GameState() : _gamePhase(GamePhase::MOVEMENT), _idOfPlayerInTurn(-1)
{
}

GamePhase Student::GameState::currentGamePhase() const
{
    return _gamePhase;
}

int Student::GameState::currentPlayer() const
{
    return _idOfPlayerInTurn;
}

void Student::GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    _gamePhase = nextPhase;
}

void Student::GameState::changePlayerTurn(int nextPlayer)
{
    _idOfPlayerInTurn = nextPlayer;
}

}
