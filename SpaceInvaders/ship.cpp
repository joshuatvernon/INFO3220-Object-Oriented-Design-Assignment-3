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
    return this->normalState;
}

ShipState* Ship::getHyperState() {
    return this->normalState;
}

ShipState* Ship::getCurrentState() {
    return this->state;
}

// Setters

void Ship::setNormalState(ShipState* state) {
    this->state = state;
}

void Ship::setFrozenState(ShipState* state) {
    this->state = state;
}

void Ship::setHyperState(ShipState* state) {
    this->state = state;
}

Ship::~Ship() {
    delete state;
    delete normalState;
    delete frozenState;
    delete hyperState;
}

}
