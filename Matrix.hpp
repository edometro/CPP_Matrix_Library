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
    constexpr Matrix(){}
    constexpr Matrix(const matrix &data){
        for(size_t i=0; i<row; ++i) for(size_t j=0; j<col; ++j)
        this->data[i][j] = data[i][j];
    }
    constexpr T* operator[](const size_t i) { return data[i]; }
    constexpr const T* operator[](const size_t i) const { return data[i]; }
    void print() const {
        for(size_t i=0; i<row; ++i){
            for(size_t j=0; j<col; ++j){
                std::cout << (*this)[i][j];
                if(j<row) std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    constexpr Matrix<T, col, row> transposit() const {
        Matrix<T, col, row> _T;
        for(size_t i=0; i<row; ++i)
        for(size_t j=0; j<col; ++j){
            _T[j][i] = (*this)[i][j];
        }
        return _T;
    }

    constexpr Matrix<T, col, row> inverse() const {
        if constexpr (row == col){
            constexpr size_t n = row;
            Matrix<T, n, n> A = *this;
            Matrix<T, n, n> I;
            for(size_t i=0; i<n; ++i){
                I[i][i] = 1;
            }

            for(size_t i=0; i<n; ++i){
                T max = abs(A[i][i]);
                for(size_t k=i+1; k<n; ++k){
                    if(max < abs(A[k][i])){
                        max = A[k][i];
                        for(size_t j=0; j<n; ++j){
                            T a_ij = A[i][j];
                            A[i][j] = A[k][j];
                            A[k][j] = a_ij;
                            T i_ij = I[i][j];
                            I[i][j] = I[k][j];
                            I[k][j] = i_ij;
                        }
                    }
                }
                if(max == 0){
                    throw std::runtime_error("Matrix is singular and cannot be inverted.");
                }
                T m = A[i][i];
                for(size_t j=0; j<n; ++j){
                    A[i][j] /= m;
                    I[i][j] /= m;
                }
                for(size_t j=0; j<n; ++j){
                    if(i != j){
                        T t = A[j][i];
                        for(size_t k=0; k<n; ++k){
                            A[j][k] -= A[i][k]*t;
                            I[j][k] -= I[i][k]*t;
                        }
                    }
                }
                
            }
            return I;
        }
        else{
            if constexpr (row > col){
                return ((*this).transposit() * (*this)).inverse() * this->transposit();
            }
            else{
                return this->transposit() * ((*this) * this->transposit()).inverse();
            }
        }
    }



    template <typename U>
    constexpr operator Matrix<U, row, col>() {
        Matrix<U, row, col> A;
        for(size_t i=0; i<row; ++i)
        for(size_t j=0; j<col; ++j){
            A[i][j] = static_cast<U>(this->data[i][j]);
        }
        return A;
    }

    template <int r = row, int c = col, std::enable_if_t<(r == 1) && (c == 1), bool> = true>
    constexpr operator T() {
        return (*this)[0][0];
    }
};

template <typename T, size_t row, size_t col>
constexpr Matrix<T, row, col> operator+(const Matrix<T, row, col> &A, const Matrix<T, row, col> &B){
    Matrix<T, row, col> C;
    for(size_t i=0; i<row; ++i)
    for(size_t j=0; j<col; ++j)
    {
        C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}

template <typename T, size_t rowA, size_t colB, size_t n>
constexpr Matrix<T, rowA, colB> operator*(const Matrix<T, rowA, n> &A, const Matrix<T, n, colB> &B){
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
constexpr Matrix<T, row, col> operator*(const Matrix<T, row, col> &A, const X k){
    Matrix<T, row, col> B;
    for(size_t i=0; i<row; ++i)
    for(size_t j=0; j<col; ++j)
    {
        B[i][j] = A[i][j]*k;
    }
    return B;
}

template <typename X, typename T, size_t row, size_t col>
constexpr Matrix<T, row, col> operator*(const X k, const Matrix<T, row, col> &A){
    Matrix<T, row, col> B;
    for(size_t i=0; i<row; ++i)
    for(size_t j=0; j<col; ++j)
    {
        B[i][j] = k*A[i][j];
    }
    return B;
}

#endif // MATRIX_HPP