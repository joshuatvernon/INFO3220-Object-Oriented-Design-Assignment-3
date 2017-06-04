#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include <QPixmap>
#include <QList>

namespace game {

class ShipState {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

public:
    virtual QList<Bullet*> shoot() { return QList<Bullet*>(); };
    virtual void move_left() {}
    virtual void move_right() {}
    virtual void move_up() {}
    virtual void move_down() {}
};
}
