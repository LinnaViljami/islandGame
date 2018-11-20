#include "gamestate.hh"

using Common::GamePhase;

namespace Student{

Student::GameState::GameState() : gamePhase_(GamePhase::MOVEMENT), idOfPlayerInTurn_(-1)
{
}

GamePhase Student::GameState::currentGamePhase() const
{
    return gamePhase_;
}

int Student::GameState::currentPlayer() const
{
    return idOfPlayerInTurn_;
}

void Student::GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    gamePhase_ = nextPhase;
}

void Student::GameState::changePlayerTurn(int nextPlayer)
{
    idOfPlayerInTurn_ = nextPlayer;
}
}
