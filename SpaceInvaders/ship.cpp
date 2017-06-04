#include "ship.h"
#include "bullet.h"
#include "config.h"
#include "shipStateFrozen.h"
#include "shipStateHyper.h"
#include "shipStateNormal.h"

namespace game {
Ship::Ship(QPixmap image, double scale, int x, int y)
        : Base(image, scale, x, y - image.height() * scale,
                  Config::getInstance()->get_SCALEDWIDTH(),
                  Config::getInstance()->get_SCALEDWIDTH(), 0),
          velocity(10), bullet_velocity(15), builder(bullet_velocity, *this, "laser", true) {
    // adjust the image size according to scale
    this->set_image(this->get_image().scaledToWidth(this->get_image().width() * scale));

    // readjust (x,y) since the image was resized
    boundaryX = Config::getInstance()->get_SCALEDWIDTH() - this->get_image().width();
    boundaryY = Config::getInstance()->get_SCALEDHEIGHT() - this->get_image().height();

    set_x(x);
    set_y(y);

    normalState = (ShipState*) new ShipStateNormal(this);
    frozenState = (ShipState*) new ShipStateFrozen(this);
    hyperState = (ShipState*) new ShipStateHyper(this);
    state = normalState;
}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
QList<Bullet*> Ship::shoot() {
    return state->shoot();
}

// Setters
void Ship::move_left() {
    state->move_left();
}

void Ship::move_right() {
    state->move_right();
}

void Ship::move_up() {
    state->move_up();
}

void Ship::move_down()  {
    state->move_down();
}

// Getters

int Ship::get_velocity() {
    return this->velocity;
}

BulletBuilder Ship::get_builder() {
    return builder;
}

ShipState* Ship::getNormalState() {
    return this->normalState;
}

ShipState* Ship::getFrozenState() {
    return this->frozenState;
}

ShipState* Ship::getHyperState() {
    return this->hyperState;
}

ShipState* Ship::getDeadState() {
    return this->deadState;
}

QString Ship::getCurrentState() {
    if (this->state == normalState) {
        return "Normal";
    } else if (this->state == frozenState) {
        return "Frozen";
    } else if (this->state == hyperState) {
        return "Hyper";
    } else {
        return "Dead";
    }
}

// Setters

void Ship::setState(ShipState* newState) {
    state = (ShipState*) newState;
    QPixmap ship;
    // Change the image to reflect the new state
    if (getCurrentState() == "Frozen") {
        ship.load(":/Images/frozenship.png");
    } else if (getCurrentState() == "Normal") {
        ship.load(":/Images/ship.png");
    } else if (getCurrentState() == "Hyper") {
        ship.load(":/Images/hypership.png");
    } else {
        ship.load(":/Images/deadship.png");
    }
    set_image(ship.scaledToWidth(ship.width() * get_scale()));
    // Reset the boundaries based upon the new image
    boundaryX = Config::getInstance()->get_SCALEDWIDTH() - this->get_image().width();
    boundaryY = Config::getInstance()->get_SCALEDHEIGHT() - this->get_image().height();
}

Ship::~Ship() {
    // Delete states but not current state as its just a pointer to one of these states
    delete normalState;
    delete frozenState;
    delete hyperState;
    delete deadState;
}

}
