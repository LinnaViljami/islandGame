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
    void testChangePlayerTurn();
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

void GamestateTest::testChangePlayerTurn()
{
    GameState testState = GameState();
    int testPlayerId = 2;
    testState.changePlayerTurn(2);
    QCOMPARE(testPlayerId, testState.currentPlayer());

}

QTEST_APPLESS_MAIN(GamestateTest)

#include "gamestatetest.moc"
