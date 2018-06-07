#include "Pixel.h"

Pixel::Pixel(int x, int y) {
    this->x = x;
    this->y = y;
}

int Pixel::GetX() {
    return x;
}

int Pixel::GetY() {
    return y;
}
