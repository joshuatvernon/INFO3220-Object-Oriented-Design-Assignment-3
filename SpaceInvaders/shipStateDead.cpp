#include "shipStateDead.h"
#include "bullet.h"
#include "config.h"

namespace game {
ShipStateDead::ShipStateDead(Ship* ship) : ship(ship)
{}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
QList<Bullet*> ShipStateDead::shoot() {
   QList<Bullet*> bullets = {};
   return bullets;
}

// Setters
void ShipStateDead::move_left() {
    ship->set_x(ship->get_x());
}

void ShipStateDead::move_right() {
    ship->set_x(ship->get_x());
}

void ShipStateDead::move_up() {
    ship->set_y(ship->get_y());
}

void ShipStateDead::move_down()  {
    ship->set_y(ship->get_y());
}

}
