#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);
    ~Rectangle();
    void print() const;
    void zoom(int factor);
    bool is_inside(int x, int y) const;
private:
    int _width;
    int _height;
};
