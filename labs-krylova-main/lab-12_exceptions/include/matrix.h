#ifndef LAB_12_EXCEPTIONS_MATRIX_H
#define LAB_12_EXCEPTIONS_MATRIX_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <cassert>


namespace Matrix {
    class Matrix {
    public:
        Matrix();

        Matrix(std::size_t r, std::size_t c);

        ~Matrix();

        void allocSpace();

        std::size_t get_rows() const;

        std::size_t get_cols() const;

        void set(std::size_t i, std::size_t j, int val);

        int get(std::size_t i, std::size_t j) const;

        void swap(Matrix &first, Matrix &second);

        bool operator==(const Matrix &that) const;

        bool operator!=(const Matrix &that) const;

        Matrix &operator+=(const Matrix &that);

        Matrix &operator*=(const Matrix &that);

        Matrix(const Matrix &that);

        Matrix &operator=(const Matrix &that);

        friend std::istream &operator>>(std::istream &in, Matrix &matrix);

        friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);

    private:
        std::size_t _rows;
        std::size_t _cols;
        size_t **_data;
    };


    class MatrixException : public std::runtime_error {
    public:
        MatrixException(const char *const message) : std::runtime_error(message) {}
    };


    class Registers {
    public:
        Registers();

        ~Registers();

        void load(const std::string &reg, const std::string &fname);

        void print(const std::string &reg);

        void add(const std::string &reg1, const std::string &reg2);

        void mul(const std::string &reg1, const std::string &reg2);

        int elem(const std::string &reg, size_t row, size_t col);

        static int check_reg(const std::string &reg);

    private:
        Matrix *matrix_list;
    };
}

#endif //LAB_12_EXCEPTIONS_MATRIX_H
