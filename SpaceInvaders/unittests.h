#ifndef UNITTESTS_H
#define UNITTESTS_H
#include <QList>
#include <QPair>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QDebug>

namespace game {
class UnitTests {

public:
    UnitTests();
    ~UnitTests() {}

    // tests
    void scoreIncreases();
    void testKeyPressEvents();
    void testSwarms();
    void testShipStates();
    void testMenuButtons();
    void testUpdateTopScores();
    void testLevels();
    void testConfigSingleton();
    void testDiagonalBullets();
    void testHunterAliens();

};

}
#endif  // UNITTESTS_H
