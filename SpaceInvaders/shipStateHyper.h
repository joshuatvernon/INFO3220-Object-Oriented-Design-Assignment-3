#ifndef SHIPSTATEHYPER_H
#define SHIPSTATEHYPER_H

#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include <QPixmap>
#include <QList>
#include "ship.h"

namespace game {

class ShipStateHyper : public ShipState {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

    Ship* ship;
public:
    ShipStateHyper(Ship* ship);
    ~ShipStateHyper() {}
    QList<Bullet*> shoot();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};
}

#endif // SHIPSTATEHYPERL_H
