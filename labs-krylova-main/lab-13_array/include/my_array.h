#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace lab_13 {

    template<typename T, std::size_t N>

    class my_array {
    public:
        T &at(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("Index is out of range");
            }
            return _data[index];
        }

        const T &at(std::size_t index) const {
            if (index >= N) {
                throw std::out_of_range("Index is out of range");
            }
            return _data[index];
        }

        T &operator[](std::size_t index) {
            return _data[index];
        }

        const T &operator[](std::size_t index) const {
            return _data[index];
        }

        bool empty() const {
            return N == 0;
        }

        std::size_t size() const {
            return N;
        }

        void fill(const T &val) {
            for (T *idx = _data; idx < _data + N; ++idx) {
                *idx = val;
            }
        }

        my_array() = default;

        my_array(const my_array &other) {
            for (size_t i = 0; i < N; ++i) {
                _data[i] = other[i];
            }
        }

    private:
        T _data[N] = {};
    };


    template<std::size_t N>
    class my_array<bool, N> {
    private:
        class Proxy {
        public:
            Proxy(char &data, std::size_t index) : _data(data), _index(index) {}

            Proxy &operator=(bool value) {
                if (value) {
                    _data |= 1 << _index;
                } else {
                    _data &= ~(1 << _index);
                }
                return *this;
            }

            Proxy &operator=(const Proxy &other) {
                if (this != &other) {
                    *this = static_cast<bool>(other);
                }
                return *this;
            }

            operator bool() const {
                return (_data >> _index) & 1;
            }

        private:
            char &_data;
            std::size_t _index;
        };

    public:
        my_array() = default;

        std::size_t size() const {
            return N;
        }

        bool empty() const {
            return N == 0;
        }

        void fill(bool val) {
            for (std::size_t i = 0; i < N; i++) {
                at(i) = val;
            }
        }

        Proxy at(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("Index is out of a range");
            }
            return Proxy(_data[index / 8], index % 8);
        }

        bool at(std::size_t index) const {
            if (index >= N) {
                throw std::out_of_range("Index is out of a range");
            }
            return _data[index / 8] & (1 << index % 8);
        }

        Proxy operator[](std::size_t index) {
            return Proxy(_data[index / 8], index % 8);
        }

        bool operator[](std::size_t index) const {
            return _data[index / 8] & (1 << index % 8);
        }

    private:
        char _data[(N + 8 - 1) / 8] = {};
    };

}  // namespace lab_13

#endif  // MY_ARRAY_H_
