#include "Scheme.hpp"
#include <stdexcept>

Scheme::Scheme(int capacity) {
    if (capacity <= 0)
        throw std::runtime_error("The capacity can't be minus.");
    figures_ = new Figure*[capacity];
    cap = capacity;
    size_ = 0;
}

Scheme::~Scheme() {
    for(int i = 0; i < size_; ++i){
        delete figures_[i];
    }
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    if (fg == nullptr)
        throw std::runtime_error("Figure is nullptr.");
    if (size_ < cap) {
        figures_[size_] = fg;
        size_++;
    }else{
        throw std::runtime_error("Capacity is ended");
    }
}

void Scheme::print_all_figures() {
    for(int i = 0; i < size_; ++i){
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    for(int i = 0; i < size_; ++i)
        if (figures_[i]->id_take() == id){
            figures_[i]->zoom(factor);
            break;
        }
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size_; ++i){
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < size_; ++i){
        if (figures_[i]->id_take() == id){
            figures_[i]->move(new_x, new_y);
            break;
        }
    }
}

void Scheme::remove_figure(int id) {
    for (int i = 0; i < size_; ++i){
        if (figures_[i]->id_take() == id){
            delete figures_[i];
            for (int ind = i + 1; ind < size_; ++ind){
                figures_[ind - 1] = figures_[ind];
            }
            size_ --;
            break;
        }
    }
}