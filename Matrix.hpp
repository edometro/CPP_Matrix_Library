/*
 * @Matrix.hpp
 *
 * ----------------------------------------------------------------------------
 * MIT License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2025 edometro
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>

template <typename T, size_t row, size_t col>
class Matrix {
    private:
    using matrix = T[row][col];
    matrix data = {};
    public:
    Matrix(){}
    Matrix(const matrix &data){
        for(size_t i=0; i<row; ++i) for(size_t j=0; j<col; ++j)
        this->data[i][j] = data[i][j];
    }
    T* operator[](const size_t i) { return data[i]; }
    const T* operator[](const size_t i) const { return data[i]; }
    void print(){
        for(size_t i=0; i<row; ++i){
            for(size_t j=0; j<col; ++j){
                std::cout << (*this)[i][j];
                if(j<row) std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    template <int r = row, int c = col, std::enable_if_t<(r == 1) && (r == 1), bool> = true>
    operator T() {
        return (*this)[0][0];
    }
};

template <typename T, size_t row, size_t col>
Matrix<T, row, col> operator+(const Matrix<T, row, col> &A, const Matrix<T, row, col> &B){
    Matrix<T, row, col> C;
    for(size_t i=0; i<row; ++i)
    for(size_t j=0; j<col; ++j)
    {
        C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}

template <typename T, size_t rowA, size_t colB, size_t n>
Matrix<T, rowA, colB> operator*(const Matrix<T, rowA, n> &A, const Matrix<T, n, colB> &B){
    Matrix<T, rowA, colB> C;
    for(size_t i=0; i<rowA; ++i)
    for(size_t j=0; j<colB; ++j)
    for(size_t k=0; k<n; ++k)
    {
        C[i][j] += A[i][k] * B[k][j];
    }
    return C;
}

template <typename T, size_t row, size_t col, typename X>
Matrix<T, row, col> operator*(const Matrix<T, row, col> &A, const X k){
    Matrix<T, row, col> B;
    for(size_t i=0; i<row; ++i)
    for(size_t j=0; j<col; ++j)
    {
        B[i][j] = A[i][j]*k;
    }
    return B;
}

template <typename X, typename T, size_t row, size_t col>
Matrix<T, row, col> operator*(const X k, const Matrix<T, row, col> &A){
    Matrix<T, row, col> B;
    for(size_t i=0; i<row; ++i)
    for(size_t j=0; j<col; ++j)
    {
        B[i][j] = k*A[i][j];
    }
    return B;
}

#endif // MATRIX_HPP