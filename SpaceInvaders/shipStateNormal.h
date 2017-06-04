#ifndef SHIPSTATENORMAL_H
#define SHIPSTATENORMAL_H

#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include <QPixmap>
#include <QList>
#include "ship.h"

namespace game {

class ShipStateNormal : public ShipState {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

    Ship* ship;
public:
    ShipStateNormal(Ship* ship);
    ~ShipStateNormal() {}
    QList<Bullet*> shoot();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};
}

#endif // SHIPSTATENORMAL_H
