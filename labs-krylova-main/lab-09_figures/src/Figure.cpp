#include "Figure.hpp"

Figure::Figure(int id, int x, int y) {
    this->x = x;
    this->y = y;
    this->id = id;
}

Figure::~Figure() = default;

void Figure::move(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Figure::id_take() {return id;}