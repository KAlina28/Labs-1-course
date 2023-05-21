#include "Circle.hpp"
#include <cstring>
#include <cstdio>
#include <stdexcept>

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    if (radius < 0)
        throw std::runtime_error("The radius can't be minus.");
    _radius = radius;

    if (label != nullptr) {
        _label = new char[strlen(label) + 1];
        strcpy(_label, label);
    }else {
        throw std::runtime_error("The label is nullptr.");
    }
}

Circle::~Circle() {
    delete[] _label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, _radius, _label);
}

void Circle::zoom(int factor) {
    if (factor < 0) {
        throw std::runtime_error("The radius can't be minus.");
    }
    _radius *= factor;
}

bool Circle::is_inside(int x, int y) const {
    return ((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= _radius * _radius);
}
