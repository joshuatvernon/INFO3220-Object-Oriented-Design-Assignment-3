#ifndef SHIPSTATEFROZEN_H
#define SHIPSTATEFROZEN_H

#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include <QPixmap>
#include <QList>
#include "ship.h"

namespace game {

class ShipStateFrozen : public ShipState {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

    Ship* ship;
public:
    ShipStateFrozen(Ship* ship);
    ~ShipStateFrozen() {}
    QList<Bullet*> shoot();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};
}

#endif // SHIPSTATEFROZEN_H
