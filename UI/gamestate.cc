#include "gamestate.hh"

using Common::GamePhase;

namespace Student{

Student::GameState::GameState() : gamePhase_(GamePhase::MOVEMENT), idOfPlayerInTurn_(-1), movesLeft_(3)
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
    if(nextPhase == Common::GamePhase::MOVEMENT){
        setMovesLeft(3);
    }
}

void Student::GameState::changePlayerTurn(int nextPlayer)
{
    idOfPlayerInTurn_ = nextPlayer;
}

int GameState::getMovesLeft()
{
    return movesLeft_;
}

void GameState::setMovesLeft(int movesLeft)
{
    movesLeft_=movesLeft;
}

}
