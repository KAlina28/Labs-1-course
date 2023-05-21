#include "matrix.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace Matrix {
    void Matrix::allocSpace() {
        try{
            _data = new size_t *[_rows];
            for (size_t i = 0; i < _rows; i++) {
                _data[i] = new size_t [_cols];
            }
        }
        catch (std::bad_alloc &e){
            delete[] _data;
            throw MatrixException("Unable to allocate memory.");
        }
    }

    Matrix::Matrix() {
        _cols = 0;
        _rows = 0;
        _data = nullptr;
    }

    Matrix::Matrix(std::size_t r, std::size_t c) {
        _rows = r;
        _cols = c;
        _data = nullptr;
        allocSpace();
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                _data[i][j] = 0;
            }
        }
    }

    Matrix::Matrix(const Matrix &m) {
        _rows = m._rows;
        _cols = m._cols;
        try {
            allocSpace();
        }
        catch (std::bad_alloc &exception) {
            delete _data;
            throw MatrixException("Unable to allocate memory.");
        }
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                _data[i][j] = m._data[i][j];
            }
        }
    }

    Matrix::~Matrix() {
        if (_data == nullptr)
            return;
        for (size_t i = 0; i < _rows; i++) {
            delete[] _data[i];
        }
        delete[] _data;
    }


    size_t Matrix::get_rows() const {
        return _rows;
    }

    size_t Matrix::get_cols() const {
        return _cols;
    }


    void Matrix::set(const size_t i, const size_t j, const int val) {
        if (i >= _rows || j >= _cols)
            throw MatrixException("ACCESS: bad index.");
        _data[i][j] = val;
    }

    int Matrix::get(const size_t i, const size_t j) const {
        if (i >= _rows || j >= _cols)
            throw MatrixException("ACCESS: bad index.");
        return _data[i][j];
    }

    void Matrix::swap(Matrix &first, Matrix &second) {
        using std::swap;

        swap(first._cols, second._cols);
        swap(first._rows, second._rows);
        swap(first._data, second._data);
    }

    Matrix &Matrix::operator=(const Matrix &m) {
        Matrix temp(m);
        swap(*this, temp);

        return *this;
    }

    bool Matrix::operator==(const Matrix &m) const {
        if (_rows != m._rows || _cols != m._cols) {
            return false;
        }
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                if (_data[i][j] != m._data[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix &m) const {
        return !(*this == m);
    }

    Matrix &Matrix::operator+=(const Matrix &that) {
        if (_rows != that._rows || _cols != that._cols) {
            throw MatrixException("ADD: dimensions do not match.");
        }
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                _data[i][j] += that._data[i][j];
            }
        }
        return *this;
    }

    Matrix &Matrix::operator*=(const Matrix &that) {
        if (_cols != that._rows) {
            throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
        }
        Matrix ans(_rows, that._cols);
        for (size_t k = 0; k < _cols; ++k) {
            for (size_t i = 0; i < _rows; ++i) {
                for (size_t j = 0; j < that._cols; ++j) {
                    ans._data[i][j] += _data[i][k] * that._data[k][j];
                }
            }
        }
        return *this = ans;
    }


    std::istream &operator>>(std::istream &in, Matrix &matrix) {
        if (!in)
            throw MatrixException("LOAD: unable to open file.");
        int rows, cols;
        in >> rows >> cols;
        if (!in){
            throw MatrixException("LOAD: invalid file format.");
        }
        matrix = Matrix(rows, cols);
        for (int i = 0; i < rows && in; ++i) {
            for (int j = 0; j < cols && in; ++j) {
                in >> matrix._data[i][j];
            }
        }
        if (!in) {
            throw MatrixException("LOAD: invalid file format.");
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
        for (size_t i = 0; i < matrix._rows; ++i) {
            for (size_t j = 0; j < matrix._cols - 1; ++j) {
                out << matrix.get(i, j) << " ";
            }
            out << matrix.get(i, matrix._cols - 1) << std::endl;
        }
        return out;
    }


    int Registers::check_reg(const std::string &reg) {
        assert(reg.size() == 2 && isdigit(reg[1]));
        return reg[1] - '0';
    }

    void Registers::load(const std::string &reg, const std::string &fname) {
        size_t reg_number = check_reg(reg);
        std::ifstream in(fname);
        Matrix matrix;
        in >> matrix;
        matrix_list[reg_number] = matrix;
    }

    void Registers::print(const std::string &reg) {
        std::cout << matrix_list[check_reg(reg)];
    }

    void Registers::add(const std::string &reg1, const std::string &reg2) {
        matrix_list[check_reg(reg1)] += matrix_list[check_reg(reg2)];
    }

    void Registers::mul(const std::string &reg1, const std::string &reg2) {
        matrix_list[check_reg(reg1)] *= matrix_list[check_reg(reg2)];
    }

    int Registers::elem(const std::string &reg, size_t row, size_t col) {
        return matrix_list[check_reg(reg)].get(row, col);
    }

    Registers::Registers() {
        matrix_list = new Matrix[10];
    }

    Registers::~Registers() {
        delete[] matrix_list;
    }

}
