#include <QString>
#include <QtTest>

class GamestateTest : public QObject
{
    Q_OBJECT

public:
    GamestateTest();

private Q_SLOTS:
    void testCase1();
};

GamestateTest::GamestateTest()
{
}

void GamestateTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GamestateTest)

#include "tst_gamestatetest.moc"
