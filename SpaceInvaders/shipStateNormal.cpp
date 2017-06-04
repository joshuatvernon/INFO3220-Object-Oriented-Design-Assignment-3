#include "shipStateNormal.h"
#include "bullet.h"
#include "config.h"

namespace game {
ShipStateNormal::ShipStateNormal(Ship* ship) : ship(ship)
{}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
QList<Bullet*> ShipStateNormal::shoot() {
    BulletBuilder builder = ship->get_builder();
    QList<Bullet*> bullets;
    bullets.append(builder.build_bullet("laser"));
    return bullets;
}

// Setters
void ShipStateNormal::move_left() {
    ship->set_x(ship->get_x() - ship->get_velocity());
}

void ShipStateNormal::move_right() {
    ship->set_x(ship->get_x() + ship->get_velocity());
}

void ShipStateNormal::move_up() {
    ship->set_y(ship->get_y() - ship->get_velocity());
}

void ShipStateNormal::move_down()  {
    ship->set_y(ship->get_y() + ship->get_velocity());
}

}
