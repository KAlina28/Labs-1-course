#ifndef MY_VECTOR_IMPL_HPP_
#define MY_VECTOR_IMPL_HPP_

#include "my_vector.hpp"

namespace containers {

    template<typename T>
    my_vector<T>::my_vector() {
        size_ = 0;
        capacity_ = 1;
        array_ = reinterpret_cast<T *>(new char[sizeof(T)]);
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        array_ = nullptr;
        size_ = 0;
        capacity_ = 1;
        reserve(n);
        size_ = n;
        for (size_t i = 0; i < size_; ++i) {
            new(array_ + i) T();
        }
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        return (size_ == 0);
    }

    template<typename T>
    void my_vector<T>::push_back(const T &t) {
        reserve(size_ + 1);
        new(array_ + size_) T(t);
        size_++;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        array_[size_ - 1].~T();
        size_--;
    }

    template<typename T>
    void my_vector<T>::clear() {
        for (size_t i = 0; i < size_; ++i) {
            array_[i].~T();
        }
        size_ = 0;
    }

    template<typename T>
    my_vector<T>::~my_vector<T>() {
        for (size_t i = 0; i < size_; ++i) {
            array_[i].~T();
        }
        delete[] reinterpret_cast<char *> (array_);
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        reserve(n);
        if (n < size_) {
            for (size_t i = n; i < size_; ++i) {
                array_[i].~T();
            }
        } else if (n > size_) {
            for (size_t i = size_; i < n; ++i) {
                new(array_ + i) T();
            }
        }
        size_ = n;
    }

    template<typename S>
    std::ostream &operator<<(std::ostream &out, const my_vector <S> &v) {
        for (size_t i = 0; i < v.size_ - 1; i++) {
            out << v[i] << " ";
        }
        out << v[v.size_ - 1];
        return out;
    }

    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    const T &my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    my_vector <T> &my_vector<T>::operator=(const my_vector &other) {
        my_vector<T> v = other;
        std::swap(capacity_, v.capacity_);
        std::swap(size_, v.size_);
        std::swap(array_, v.array_);
        return *this;
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (size_t i = 0; i < size_; ++i) {
            new(array_ + i) T(other[i]);
        }
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n <= capacity_) return;
        size_t cap = capacity_;
        while (cap < n) { cap *= 2; }
        T *arr = reinterpret_cast<T *>(new char[sizeof(T) * cap]);
        for (size_t i = 0; i < size_; ++i) {
            new(arr + i) T(array_[i]);
            array_[i].~T();
        }
        delete[] reinterpret_cast<char *> (array_);
        array_ = reinterpret_cast<T *>(arr);
        capacity_ = cap;
    }

}
#endif  // MY_VECTOR_IMPL_HPP_
