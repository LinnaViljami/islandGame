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

QTEST_APPLESS_MAIN(GamestateTest)

#include "gamestatetest.moc"
