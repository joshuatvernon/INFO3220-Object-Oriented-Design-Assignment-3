#ifndef SHIP_H
#define SHIP_H

#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include "shipState.h"
#include <QPixmap>
#include <QDebug>

namespace game {

class Ship : public Base {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

private:
    int velocity;
    int bullet_velocity;
    BulletBuilder builder;

    // Abstract State
    ShipState* state;

    // Concrete States
    ShipState* normalState;
    ShipState* frozenState;
    ShipState* hyperState;

public:
    Ship(QPixmap image, double scale, int x, int y);
    QList<Bullet *> shoot();
    void move_left();
    void move_right();
    void move_up();
    void move_down();

    // Getters
    int get_velocity();
    BulletBuilder get_builder();
    ShipState* getNormalState();
    ShipState* getFrozenState();
    ShipState* getHyperState();
    QString getCurrentState();

    // Setters
    void setState(ShipState* newState);

    virtual ~Ship();
};
}

#endif // SHIP_H
