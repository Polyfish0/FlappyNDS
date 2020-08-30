#include "pipe.h"

Pipe::Pipe(float posX, int shift, int thickness, int points) {
    this->posX = posX;
    this->shift = shift;
    this->thickness = thickness;
    this->points = points;
}

float Pipe::getPosX() {
    return this->posX;
}

int Pipe::getShift() {
    return this->shift;
}

int Pipe::getThickness() {
    return this->thickness;
}

int Pipe::getPoints() {
    return this->points;
}

void Pipe::setPosX(float x) {
    this->posX = x;
}

void Pipe::setShift(int shift) {
    this->shift = shift;
}

void Pipe::setThickness(int thickness) {
    this->thickness = thickness;
}

void Pipe::setPoints(int points) {
    this->points = points;
}