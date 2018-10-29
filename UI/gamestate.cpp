#include "gameboard.hh"
using Common::GamePhase;

namespace Student{

Student::GameState::GameState()
{

}
virtual GamePhase currentGamePhase() const = 0;


}
