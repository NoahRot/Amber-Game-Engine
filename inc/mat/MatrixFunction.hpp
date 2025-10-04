#pragma once

#include <cmath>

#include "Matrix.hpp"
#include "Vector.hpp"

namespace mat {

//    ___     _                     _                          _              
//   | __|_ _| |_ ___ _ _ _ _  __ _| |  ___ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | _|\ \ /  _/ -_) '_| ' \/ _` | | / _ \ '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//   |___/_\_\\__\___|_| |_||_\__,_|_| \___/ .__/\___|_| \__,_|\__\___/_| /__/
//                                         |_|                                

/// @brief Stream operator, write the matrix into a stream
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param stream The stream
/// @param m The matrix
/// @return The stream with the modifications
template<typename T, uint32_t N, uint32_t M>
std::ostream& operator<<(std::ostream& stream, const Matrix<T,N,M>& m) {
    stream << "Mat[" << N << "x" << M << "]:\n  ";
    for (uint32_t i(0) ; i < N ; ++i) {
        for (uint32_t j(0) ; j < M ; ++j) {
            stream << m(i,j);
            j == M-1 ? stream << "\n  " : stream << " " ;
        }
    }
    return stream;
}

/// @brief Add a scalar to each element of the matrix
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The matrix
/// @param a The scalar
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator+(Matrix<T,N,M> m1, T a) {
    return m1 += a;
}

/// @brief Add a scalar to each element of the matrix
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param a The scalar
/// @param m1 The matrix
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator+(T a, Matrix<T,N,M> m1) {
    return m1 += a;
}

/// @brief Substract a scalar to each element of the matrix
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The matrix
/// @param a The scalar
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator-(Matrix<T,N,M> m1, T a) {
    return m1 -= a;
}

/// @brief Substract element of the matrix by a scalar
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param a The scalar
/// @param m1 The matrix
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator-(T a, Matrix<T,N,M> m1) {
    return m1 -= a;
}

/// @brief Multiply each component of a matrix by a scalar
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The matrix
/// @param a The scalar
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator*(Matrix<T,N,M> m1, T a) {
    return m1 *= a;
}

/// @brief Multiply each component of a matrix by a scalar
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param a The scalar
/// @param m1 The matrix
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator*(T a, Matrix<T,N,M> m1) {
    return m1 *= a;
}

/// @brief Divide each component of a matrix by a scalar
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The matrix
/// @param a The scalar
/// @return The new matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator/(Matrix<T,N,M> m1, T a) {
    return m1 /= a;
}

/// @brief Addition of two matrices
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The addition of the matrices
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator+(Matrix<T,N,M> m1, const Matrix<T,N,M>& m2) {
    return m1 += m2;
}

/// @brief Substraction of two matrices
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The substraction of the matrices
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator-(Matrix<T,N,M> m1, const Matrix<T,N,M>& m2) {
    return m1 -= m2;
}

/// @brief Multiplication of each elements of two matrices
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The multiplication of each element of the matrices
/// @warning This is not the matrix product. Use dot function for the matrix product
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator*(Matrix<T,N,M> m1, const Matrix<T,N,M>& m2) {
    return m1 *= m2;
}

/// @brief Division of each elements of two matrices
/// @tparam T The type of matrix
/// @tparam N Row
/// @tparam M Column
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The division of each element of the matrices
/// @warning This is not the matrix product. Use dot function for the matrix product
template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> operator/(Matrix<T,N,M> m1, const Matrix<T,N,M>& m2) {
    return m1 /= m2;
}

//    ___             _   _             
//   | __|  _ _ _  __| |_(_)___ _ _  ___
//   | _| || | ' \/ _|  _| / _ \ ' \(_-<
//   |_| \_,_|_||_\__|\__|_\___/_||_/__/
//                                      

template<typename T, uint32_t N, uint32_t M>
T min(const Matrix<T,N,M>& m) {
    T result = m(0,0);
    for (auto i : m) {
        if (i < result) {
            result = i;
        }
    }
    return result;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> min(Matrix<T,N,M> m, T a) {
    for (auto& i : a) {
        if (a < i) {
            i = a;
        }
    }
    return m;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> min(Matrix<T,N,M> m1, const Matrix<T,N,M>& m2) {
    for (uint32_t i(0) ; i < N*M ; ++i) {
        if (m2[i] < m1[i]) {
            m1[i] = m2[i];
        }
    }
    return m1;
}

template<typename T, uint32_t N, uint32_t M>
T max(const Matrix<T,N,M>& m) {
    T result = m(0,0);
    for (auto i : m) {
        if (i > result) {
            result = i;
        }
    }
    return result;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> max(Matrix<T,N,M> m, T a) {
    for (auto& i : a) {
        if (a > i) {
            i = a;
        }
    }
    return m;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> max(Matrix<T,N,M> m1, const Matrix<T,N,M>& m2) {
    for (uint32_t i(0) ; i < N*M ; ++i) {
        if (m2[i] > m1[i]) {
            m1[i] = m2[i];
        }
    }
    return m1;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> abs(Matrix<T,N,M> m) {
    T zero(0);
    for (auto& i : m) {
        if (i < zero) {
            i = -i;
        }
    }
    return m;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M> sign(Matrix<T,N,M> m) {
    T zero(0);
    T one(1);
    T mone(-1);
    for (auto& i : m) {
        if (i < zero) {
            i = mone;
        }else if(i > zero) {
            i = one;
        }else{
            i = zero;
        }
    }
    return m;
}

/// @brief Transform a vector to a row matrix
/// @tparam T Type
/// @tparam N Size
/// @param v The vector
/// @return The row matrix
template<typename T, uint32_t N>
Matrix<T,1,N> to_row_matrix(const Vector<T,N>& v) {
    Matrix<T,1,N> result;
    auto it(v.begin());
    for (auto& i : result) {
        i = *it;
        ++it;
    }
    return result;
}

/// @brief Transform a vector to a column matrix
/// @tparam T Type
/// @tparam N Size
/// @param v The vector
/// @return The column matrix
template<typename T, uint32_t N>
Matrix<T,N,1> to_column_matrix(const Vector<T,N>& v) {
    Matrix<T,N,1> result;
    auto it(v.begin());
    for (auto& i : result) {
        i = *it;
        ++it;
    }
    return result;
}

/// @brief Transform a column matrix to a vector
/// @tparam T Type
/// @tparam N Size
/// @param m The column matrix
/// @return The vector
template<typename T, uint32_t N>
Vector<T,N> to_vector(const Matrix<T,N,1>& m) {
    Vector<T,N> result;
    auto it(m.begin());
    for (auto& i : result) {
        i = *it;
        ++it;
    }
    return result;
}

/// @brief Transform a row matrix to a vector
/// @tparam T Type
/// @tparam N Size
/// @param m The row matrix
/// @return The vector
template<typename T, uint32_t N>
Vector<T,N> to_vector(const Matrix<T,1,N>& m) {
    Vector<T,N> result;
    auto it(m.begin());
    for (auto& i : result) {
        i = *it;
        ++it;
    }
    return result;
}

/// @brief Matrix product
/// @tparam T Type
/// @tparam N Row of the first matrix
/// @tparam M Column of the first matrix and row of the second matrix
/// @tparam P Column of the second matrix
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The result matrix
template<typename T, uint32_t N, uint32_t M, uint32_t P>
Matrix<T,N,P> dot(const Matrix<T,N,M>& m1, const Matrix<T,M,P>& m2) {
    Matrix<T,N,P> result;

    for (uint32_t i(0) ; i < N ; ++i) {
        for (uint32_t j(0) ; j < P ; ++j) {
            T tmp(0);
            for (uint32_t k(0) ; k < M ; ++k) {
                tmp += m1(i,k) * m2(k,j); 
            }
            result(i,j) = tmp;
        }
    }

    return result;
}

/// @brief Matrix - vector product
/// @tparam T Type
/// @tparam N Row of the matrix
/// @tparam M Column of the matrix and size of the vector
/// @param m The matrix
/// @param v The vector
/// @return The result vector
template<typename T, uint32_t N, uint32_t M>
BaseVector<T,N> dot(const Matrix<T,N,M>& m, const BaseVector<T,M>& v) {
    BaseVector<T,N> result;

    for (uint32_t i(0) ; i < N ; ++i) {
        T tmp(0);
        for (uint32_t k(0) ; k < M ; ++k) {
            tmp += m(i,k) * v[k];
        }
        result[i] = tmp;
    }

    return result;
}

/// @brief Vector - matrix product
/// @tparam T Type
/// @tparam N Row of the matrix and size of the vector
/// @tparam M Column of the matrix
/// @param v The vector
/// @param m The matrix
/// @return The result vector
template<typename T, uint32_t N, uint32_t M>
BaseVector<T,M> dot(const BaseVector<T,N>& v, const Matrix<T,N,M>& m) {
    BaseVector<T,M> result;

    for (uint32_t i(0) ; i < M ; ++i) {
        T tmp(0);
        for (uint32_t k(0) ; k < N ; ++k) {
            tmp += v[k] * m(k,i);
        }
        result[i] = tmp;
    }

    return result;
}

/// @brief Get the identity matrix
/// @tparam T Type
/// @tparam N Row and column of the matrix
/// @return The identity matrix
template<typename T, uint32_t N>
Matrix<T,N,N> identity() {
    Matrix<T,N,N> result;
    for (uint32_t i(0) ; i < N ; ++i) {
        result(i,i) = 1;
    }
    return result;
}

/// @brief Get the transpose of a matrix
/// @tparam T Type
/// @tparam N Row of the matrix
/// @tparam M Column of the matrix
/// @param m The matrix
/// @return The transpose matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<T,M,N> transpose(const Matrix<T,N,M>& m) {
    Matrix<T,M,N> result;
    for (uint32_t i(0) ; i < N ; ++i) {
        for (uint32_t j(0) ; j < M ; ++j) {
            result(j,i) = m(i,j);
        }
    }
    return result;
}

/// @brief Transpose the matrix itself
/// @tparam T Type
/// @tparam N Row and column of the matrix
/// @param m The matrix
template<typename T, uint32_t N>
void self_transpose(Matrix<T,N,N>& m) {
    for (uint32_t i(0) ; i < N ; ++i) {
        for (uint32_t j(i+1) ; j < N ; ++j) {
            std::swap(m(i,j), m(j,i));
        }
    }
}

/// @brief Direct sum of two matrices
/// @tparam T Type
/// @tparam N Row of the first matrix
/// @tparam M Column of the first matrix
/// @tparam P Row of the second matrix
/// @tparam Q Column of the second matrix
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The direct sum of the matrices
template<typename T, uint32_t N, uint32_t M, uint32_t P, uint32_t Q>
Matrix<T,N+P,M+Q> direct_sum(const Matrix<T,N,M>& m1, const Matrix<T,P,Q>& m2) {
    Matrix<T,N+P,M+Q> result;

    for (uint32_t i(0) ; i < N ; ++i) {
        for (uint32_t j(0) ; j < M ; ++j) {
            result(i,j) = m1(i,j);
        }
    }

    for (uint32_t i(0) ; i < P ; ++i) {
        for (uint32_t j(0) ; j < Q ; ++j) {
            result(i+N,j+M) = m2(i,j);
        }
    }

    return result;
}

/// @brief Kronecker product of two matrices
/// @tparam T Type
/// @tparam N Row of the first matrix
/// @tparam M Column of the first matrix
/// @tparam P Row of the second matrix
/// @tparam Q Column of the second matrix
/// @param m1 The first matrix
/// @param m2 The second matrix
/// @return The kronecker product of the matrices
template<typename T, uint32_t N, uint32_t M, uint32_t P, uint32_t Q>
Matrix<T,N*P,M*Q> kronecker_product(const Matrix<T,N,M>& m1, const Matrix<T,P,Q>& m2) {
    Matrix<T,N*P,M*Q> result;

    for (uint32_t i(0) ; i < N*P ; ++i) {
        for (uint32_t j(0) ; j < M*Q ; ++j) {
            result(i,j) = m1(i/P,j/Q) * m2(i%P,j%Q);
        }
    }

    return result;
}

/// @brief Compute the determinant of a matrix
/// @tparam T Type
/// @tparam N Row and column of the first matrix
/// @param m The matrix
/// @return The determinant of the matrix
template<typename T, uint32_t N>
T determinant(Matrix<T,N,N> m) {
    T sign = T(1);

    for(uint32_t k = 0 ; k < N - 1 ; k++) {

        //Pivot - row swap needed
        if(m(k,k) == T(0)) {
            uint32_t j = 0;
            for(j = k + 1 ; j < N ; j++) {
                if(m(j,k) != T(0)) {       
                    std::swap(m[j], m[k]);
                    sign = -sign;
                    break;
                }
            }

            //No entries != 0 found in column k -> det = 0
            if(j == N) {
                return 0;
            }
        }

        //Apply formula
        for (uint32_t i(k + 1) ; i < N ; i++) {
            for (uint32_t j(k + 1) ; j < N ; j++) {
                m(i,j) = m(k,k) * m(i,j) - m(i,k) * m(k,j);
                if(k != 0) {
                    m(i,j) /= m(k-1,k-1);
                }
            }
        }
    }

    return sign * m(N-1,N-1);
}

/// @brief Compute the inverse of a matrix
/// @tparam T Type
/// @tparam N Row and column of the first matrix
/// @param m The matrix
/// @return The inverse of the matrix
/// @warning Does not check if the determinant is non null
template<typename T, uint32_t N>
Matrix<T,N,N> inverse(Matrix<T,N,N> m) {
    // The matrix result is the augmented part of the matrix m
    Matrix<T,N,N> result;
    for (uint32_t i(0) ; i < N ; ++i) {
        result(i,i) = 1;
    }
    T temp;
 
    // Interchange the row of matrix,
    // interchanging of row will start from the last row
    for (uint32_t i(N-1); i > 0; i--) {
 
        // Swapping each and every element of the two rows
        for (uint32_t j(0) ; j < N ; ++j) {
            std::swap(result(i-1,j), result(i,j));
            std::swap(m(i-1,j), m(i,j));
        }
    }
 
    // Replace a row by sum of itself and a
    // constant multiple of another row of the matrix
    for (uint32_t i(0) ; i < N ; i++) {
        for (uint32_t j(0); j < N; j++) {
 
            if (j != i) {
                temp = m(j,i) / m(i,i);
                for (uint32_t k(0) ; k < 2 * N ; k++) {
                    
                    if (k < N){
                        m(j,k) -= m(i,k) * temp;
                    }else{
                        result(j,k-N) -= result(i,k-N) * temp;
                    }
                }
            }
        }
    }
 
    // Multiply each row by a nonzero integer.
    // Divide row element by the diagonal element
    for (uint32_t i(0) ; i < N ; i++) {
        temp = m(i,i);
        for (uint32_t j(0) ; j < 2 * N ; j++) {
            if (j < N){
                m(i,j) = m(i,j) / temp;
            }else{
                result(i,j-N) = result(i,j-N) / temp;
            }
        }
    }
  
    return result;
}

/// @brief Expand a matrix (from [N x N] to [N+1 x N+1])
/// @tparam T Type
/// @tparam N Row and column of the first matrix
/// @param m The matrix
/// @return The expand matrix
template<typename T, uint32_t N>
Matrix<T,N+1,N+1> expand(const Matrix<T,N,N>& m) {
    Matrix<T,N+1,N+1> result;
    std::array<T,N> tmp;

    for (uint32_t i(0) ; i < N ; ++i) {
        for (uint32_t j(0) ; j < N ; ++j) {
            result(i,j) = m(i,j);      
        }
    }
    result(N,N) = (T)1;

    return result;
}

/// @brief Compute the exponential of a matrix
/// @tparam T Type of matrix
/// @tparam N Row and column
/// @param m The matrix
/// @param tolerence Tolerence of the computation
/// @param max_iteration Maximum number of iterations
/// @return The exponential of a matrix
/// @warning Tolerence must be smaller than 1, max_iteration must be smaller than 33
template<typename T, uint32_t N>
Matrix<T,N,N> exp(const Matrix<T,N,N>& m, T tolerence = 1e-3, uint32_t max_iteration = 30) {
    T one(1);
    uint32_t fact(1);                       // Factorial
    Matrix<T,N,N> m_pow = identity<T,N>();  // m power k
    Matrix<T,N,N> previous;                 // Previous result
    Matrix<T,N,N> result = identity<T,N>(); // Current result

    // Cases k > 0
    for (uint32_t k(1) ; k < max_iteration ; ++k) {
        // Apply Taylor series
        fact *= k;
        m_pow = dot(m_pow, m);
        result += one/fact * m_pow;

        // Check difference
        T delta = max(abs(previous - result));
        if (delta < tolerence) {
            return result;
        }

        // Change previous
        previous = result;
    }

    return result;
}

}