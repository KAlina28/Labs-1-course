#include "Rectangle.hpp"
#include <cstdio>
#include <stdexcept>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    if (width <= 0 || height <= 0)
        throw std::runtime_error("The parameters can't be minus.");
    _width = width;
    _height = height;
}

Rectangle::~Rectangle() = default;

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, _width, _height);
}

void Rectangle::zoom(int factor) {
    if (factor < 0) {
        throw std::runtime_error("The parameters can't be minus.");
    }
    _width *= factor;
    _height *= factor;
}

bool Rectangle::is_inside(int x, int y) const {
    return (this->x - _width / 2 <= x && x <= this->x + _width / 2 && this->y - _height / 2 <= y &&
            y <= this->y + _height / 2);
}