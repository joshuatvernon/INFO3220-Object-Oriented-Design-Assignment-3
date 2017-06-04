#include "shipStateHyper.h"
#include "bullet.h"
#include "config.h"

namespace game {
ShipStateHyper::ShipStateHyper(Ship* ship) : ship(ship)
{}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
QList<Bullet*> ShipStateHyper::shoot() {
    BulletBuilder builder = ship->get_builder();
    QList<Bullet*> bullets;
    ship->set_x(ship->get_x() - 20);
    bullets.append(builder.build_bullet("laser"));
    ship->set_x(ship->get_x() + 40);
    bullets.append(builder.build_bullet("laser"));
    ship->set_x(ship->get_x() - 20);
    return bullets;
}

// Setters
void ShipStateHyper::move_left() {
    ship->set_x(ship->get_x() - (ship->get_velocity() * 2));
}

void ShipStateHyper::move_right() {
    ship->set_x(ship->get_x() + (ship->get_velocity() * ));
}

void ShipStateHyper::move_up() {
    ship->set_y(ship->get_y() - (ship->get_velocity() * 2));
}

void ShipStateHyper::move_down()  {
    ship->set_y(ship->get_y() + (ship->get_velocity() * 2));
}

}
