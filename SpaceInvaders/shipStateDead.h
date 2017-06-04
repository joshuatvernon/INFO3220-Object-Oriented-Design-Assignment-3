#ifndef SHIPSTATEDEAD_H
#define SHIPSTATEDEAD_H

#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include <QPixmap>
#include <QList>
#include "ship.h"

namespace game {

class ShipStateDead : public ShipState {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

    Ship* ship;
public:
    ShipStateDead(Ship* ship);
    ~ShipStateDead() {}
    QList<Bullet*> shoot();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};
}

#endif // SHIPSTATEDEAD_H
