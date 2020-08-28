#include "pipe.h"

Pipe::Pipe(float posX, int shift) {
    this->posX = posX;
    this->shift = shift;
}

float Pipe::getPosX() {
    return this->posX;
}

int Pipe::getShift() {
    return this->shift;
}

void Pipe::setPosX(float x) {
    this->posX = x;
}

void Pipe::setShift(int shift) {
    this->shift = shift;
}