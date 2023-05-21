#pragma once

#include "Figure.hpp"
#include <cstdio>

class Scheme {
public:
    Scheme(int capacity); 
    ~Scheme();

    void push_back_figure(Figure* fg);//done
    void remove_figure(int id); //done  элементы смещаются влево

    void print_all_figures();//done
    void zoom_figure(int id, int factor);//done
    Figure* is_inside_figure(int x, int y); // done если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y); // done

private:
    // ...
    int size_;
    int cap;
    Figure** figures_; // размер массива задается в конструкторе и больше не растет
};
