#include "shipStateFrozen.h"
#include "bullet.h"
#include "config.h"

namespace game {
ShipStateFrozen::ShipStateFrozen(Ship* ship) : ship(ship)
{}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
QList<Bullet*> ShipStateFrozen::shoot() {
   QList<Bullet*> bullets = {};
   return bullets;
}

// Setters
void ShipStateFrozen::move_left() {
    ship->set_x(ship->get_x());
}

void ShipStateFrozen::move_right() {
    ship->set_x(ship->get_x());
}

void ShipStateFrozen::move_up() {
    ship->set_y(ship->get_y());
}

void ShipStateFrozen::move_down()  {
    ship->set_y(ship->get_y());
}

}
