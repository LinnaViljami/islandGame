#include <QString>
#include <QtTest>
#include "gamestate.hh"

using Student::GameState;
using Common::GamePhase;

Q_DECLARE_METATYPE(GameState);
Q_DECLARE_METATYPE(GamePhase);


class GamestateTest : public QObject
{
    Q_OBJECT

public:
    GamestateTest();

private Q_SLOTS:
    void testChangeGamePhase();
    void testChangePlayerTurn();
    void testCurrentGamePhase();
    void testCurrentGamePhase_data();
    void testCurrentPlayer();
    void testCurrentPlayer_data();
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

void GamestateTest::testCurrentGamePhase()
{
    GamePhase defaultPhase = GamePhase::MOVEMENT;
    QFETCH(GamePhase, expectedPhase);
    QFETCH(GameState, newState);

    QCOMPARE(newState.currentGamePhase(), defaultPhase);
    newState.changeGamePhase(expectedPhase);
    QCOMPARE(newState.currentGamePhase(), expectedPhase);
}

void GamestateTest::testCurrentGamePhase_data()
{
    QTest::addColumn<GamePhase>("expectedPhase");
    QTest::addColumn<GameState>("newState");

    QTest::newRow("Movement") << GamePhase::MOVEMENT << GameState();
    QTest::newRow("Sinking") << GamePhase::SINKING << GameState();
    QTest::newRow("Spinning") << GamePhase::SPINNING << GameState();
}

void GamestateTest::testCurrentPlayer()
{
    QFETCH(int, expectedPlayer);
    QFETCH(GameState, newState);
    if(expectedPlayer != -1){
        newState.changePlayerTurn(expectedPlayer);
    }
    QCOMPARE(newState.currentPlayer(), expectedPlayer);
}

void GamestateTest::testCurrentPlayer_data()
{
    QTest::addColumn<int>("expectedPlayer");
    QTest::addColumn<GameState>("newState");

    QTest::newRow("DefaultPlayer") << -1 << GameState();
    QTest::newRow("Player1") << 1 << GameState();
    QTest::newRow("Player3") << 3 << GameState();
    QTest::newRow("Player244") << 244 << GameState();
}

QTEST_APPLESS_MAIN(GamestateTest)

#include "gamestatetest.moc"
