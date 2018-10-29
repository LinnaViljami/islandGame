#include <QString>
#include <QtTest>
#include "gamestate.hh"

using Student::GameState;
using Common::GamePhase;

class GamestateTest : public QObject
{
    Q_OBJECT

public:
    GamestateTest();

private Q_SLOTS:
    void testChangeGamePhase();
};

GamestateTest::GamestateTest()
{
}

void GamestateTest::testChangeGamePhase()
{
    GameState testState = GameState();
    GamePhase testPhase = GamePhase::SINKING;
    testState.changeGamePhase(GamePhase::SINKING);
    QCOMPARE(testPhase, testState.currentGamePhase());
}

QTEST_APPLESS_MAIN(GamestateTest)

#include "gamestatetest.moc"
