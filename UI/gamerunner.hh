#ifndef GAMERUNNER_HH
#define GAMERUNNER_HH

#include <QObject>
#include "igamerunner.hh"

namespace Student {

class gamerunner : public QObject
{
    Q_OBJECT
public:
    gamerunner(std::shared_ptr<Common::IGameRunner> gamerunner);
private:
    std::shared_ptr<Common::IGameRunner> _gamerunner;
};
}
#endif // GAMERUNNER_HH
