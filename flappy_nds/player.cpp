#include "player.h"

float Player::getY() {
    return this->y;
}

bool Player::isAlive() {
    return this->alive;
}

void Player::setY(float y) {
    this->y = y;
}

void Player::setAlive(bool alive) {
    this->alive = alive;
}