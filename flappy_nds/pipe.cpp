#include "pipe.h"

Pipe::Pipe(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;
}

float Pipe::getPosX() {
    return this->posX;
}

float Pipe::getPosY() {
    return this->posY;
}