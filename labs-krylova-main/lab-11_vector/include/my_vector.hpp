#ifndef MY_VECTOR_HPP_
#define MY_VECTOR_HPP_

#include <cstddef>
#include <cstring>
#include <ostream>
#include <cassert>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector();

        explicit my_vector(std::size_t n);

        my_vector(const my_vector &other);

        my_vector &operator=(const my_vector &other);

        ~my_vector();

        std::size_t size() const;

        std::size_t capacity() const;

        bool empty() const;

        void resize(std::size_t n);

        void reserve(std::size_t n);

        T &operator[](std::size_t index);

        const T &operator[](std::size_t index) const;

        void push_back(const T &t);

        void pop_back();

        void clear();

        template<typename S>
        friend std::ostream &operator<<(std::ostream &out, const my_vector<S> &v);


    private:
        size_t capacity_;
        size_t size_;
        T *array_;
    };

}

#include "my_vector_impl.hpp"

#endif  // MY_VECTOR_HPP_
