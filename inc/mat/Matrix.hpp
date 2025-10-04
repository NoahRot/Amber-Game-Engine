#pragma once

#include "Vector.hpp"
#include "VectorFunction.hpp"

#include <array>

namespace mat {

/*
Matrix (NxM)

Matrix representation :
|a1,1    a1,2    ...    a1,M|
|a2,1    a2,2    ...    a2,M|
|...     ...     ...    ... |
|aN,1    aN,2    ...    aN,M|

Store the component as :
[a1,1 a2,1 a3,1 ... aN,1 a1,2 a2,2 a3,2 ... a1,M a2,M a3,M ... aN,M]

Index of ai,j = i + j*N 
*/

//     ___ _            
//    / __| |__ _ ______
//   | (__| / _` (_-<_-<
//    \___|_\__,_/__/__/
//                      

/// @brief Mathematical matrix
/// @tparam T Type of matrix
/// @tparam N Row
/// @tparam M Column
template<typename T, uint32_t N, uint32_t M>
class Matrix{
public:
    // === Iterators ===
    typedef T* iterator;
    typedef const T* const_iterator;

public:

//     ___             _               _           
//    / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ 
//   | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
//    \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|  
//                                                 

    /// @brief Default constructor, fill the matri with value 0
    Matrix();

    /// @brief Constructor, fill the matrix with a value
    /// @param fill_val Value that fill the matrix
    Matrix(T fill_val);

    /// @brief Constructor, copy the data
    /// @param start First element to copy
    Matrix(T* start);

    /// @brief Constructor, copy an initializer list of vector
    /// @param l Initializer list of vector
    Matrix(const std::initializer_list<Vector<T,N>>& init_list);


    /// @brief Constructor, copy a initializer list
    /// @param l Initializer list
    Matrix(const std::initializer_list<T>& init_list);

    /// @brief Constructor, copy an array
    /// @param l Initial array
    Matrix(const std::array<T, N*M>& init_array);

    /// @brief Constructor, copy an array of vectors
    /// @param l Array of vectors
    Matrix(const std::array<Vector<T, N>, M>& init_array);

//    __  __     _   _            _    
//   |  \/  |___| |_| |_  ___  __| |___
//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
//   |_|  |_\___|\__|_||_\___/\__,_/__/
//                                     

    // === Utils ===

    /// @brief Get the components array of the matrix
    /// @return A constant reference to the components
    const std::array<T,N*M>& data() const { return m_component; }

    /// @brief Get the size of the matrix
    /// @param n Reference to the number of row
    /// @param m Reference to the number of column
    void size(uint32_t& n, uint32_t& m) const { n=N; m=M; }

    /// @brief Copy data into the matrix
    /// @param start A pointer to the first element that will be copy
    void copy(T* start);

    /// @brief Get the number of row
    /// @return The number of row
    uint32_t row() const { return N; }

    /// @brief Get the number of column
    /// @return The number of column
    uint32_t column() const { return M; }

    // === Iterators ===
    
    /// @brief Get the begin iterator
    /// @return The begin iterator
    iterator begin() { return &m_component[0]; }

    /// @brief Get the constant begin iterator
    /// @return The constant begin iterator
    const_iterator begin() const { return &m_component[0]; }

    /// @brief Get the end iterator
    /// @return The end iterator
    iterator end() { return &m_component[0] + N*M; }
    
    /// @brief Get the constant end iterator
    /// @return The constant end iterator
    const_iterator end() const { return &m_component[0] + N*M; }

//     ___                     _              
//    / _ \ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | (_) | '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//    \___/| .__/\___|_| \__,_|\__\___/_| /__/
//         |_|                                

    // === Accessor ===

    /// @brief Accessor to the element (i,j)
    /// @param i Row
    /// @param j Column
    /// @return A constant reference to the element (i,j) 
    const T& operator()(uint32_t i, uint32_t j) const { return m_component[i + j*N]; }

    /// @brief Accessor to the element (i,j)
    /// @param i Row
    /// @param j Column
    /// @return A reference to the element (i,j) 
    T& operator()(uint32_t i, uint32_t j) { return m_component[i + j*N]; }

    /// @brief Accessor to the i th column vector
    /// @param i Column
    /// @return A constant reference to the column vector i
    const Vector<T,N>& operator[](uint32_t i) const { return *((Vector<T,N>*)(&m_component[i*N])); }

    /// @brief Accessor to the i th column vector
    /// @param i Column
    /// @return A reference to the column vector i
    Vector<T,N>& operator[](uint32_t i) { return *((Vector<T,N>*)(&m_component[i*N])); }

    // === internal operators ===

    /// @brief Sum each component with a scalar
    /// @param a Scalar
    /// @return Reference to the matrix
    Matrix& operator+=(T a);

    /// @brief Substract each component with a scalar
    /// @param a Scalar
    /// @return Reference to the matrix
    Matrix& operator-=(T a);

    /// @brief Multiply each component with a scalar
    /// @param a Scalar
    /// @return Reference to the matrix
    Matrix& operator*=(T a);
    
    /// @brief Divide each component with a scalar
    /// @param a Scalar
    /// @return Reference to the matrix
    Matrix& operator/=(T a);

    /// @brief Add two matrices
    /// @param v Matrix
    /// @return Reference to the matrix
    Matrix& operator+=(const Matrix<T,N,M>& v);

    /// @brief Substract two matrices
    /// @param v Matrix
    /// @return Reference to the matrix
    Matrix& operator-=(const Matrix<T,N,M>& v);

    /// @brief Multiply each element of the two matrices
    /// @param v Matrix
    /// @return Reference to the matrix
    /// @warning It is not a matrix product, use the function dot
    Matrix& operator*=(const Matrix<T,N,M>& v);

    /// @brief Divide each element of the two matrices
    /// @param v Matrix
    /// @return Reference to the matrix
    Matrix& operator/=(const Matrix<T,N,M>& v);

private:
    // Components of the matrix
    std::array<T,N*M> m_component;
};


// ===================================================================================================
// ===================================================================================================


//    ___       __ _      _ _   _             
//   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  ___
//   | |) / -_)  _| | ' \| |  _| / _ \ ' \(_-<
//   |___/\___|_| |_|_||_|_|\__|_\___/_||_/__/
//                                            


template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix() {
    m_component.fill(T(0));
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix(T fill_val) {
    m_component.fill(fill_val);
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix(T* start) {
    std::copy(start, start + N*M, m_component.begin());
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix(const std::initializer_list<Vector<T,N>>& init_list) {
    m_component.fill(T(0));
    uint32_t i(0);
    for(const Vector<T,N>& v : init_list) {
        for (auto element : v) {
            m_component[i] = element;
            ++i;
        }
    }
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix(const std::initializer_list<T>& init_list) {
    m_component.fill(T(0));
    uint32_t end = std::min((size_t)(N*M), init_list.size());
    std::copy(init_list.begin(), init_list.begin() + end, m_component.begin());
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix(const std::array<T, N*M>& init_array)
: m_component(init_array)
{}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>::Matrix(const std::array<mat::Vector<T, N>, M>& init_array) {
    std::copy(&init_array[0][0], &init_array[0][0] + N*M, m_component.begin());
}

template<typename T, uint32_t N, uint32_t M>
void Matrix<T,N,M>::copy(T* start) {
    std::copy(start, start + N*M, m_component.begin());
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator+=(T a) {
    for (auto& i : m_component) {
        i += a;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator-=(T a) {
    for (auto& i : m_component) {
        i -= a;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator*=(T a) {
    for (auto& i : m_component) {
        i *= a;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator/=(T a) {
    for (auto& i : m_component) {
        i /= a;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator+=(const Matrix<T,N,M>& v) {
    const_iterator it(v.begin());
    for (auto& i : m_component) {
        i += *it;
        ++it;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator-=(const Matrix<T,N,M>& v) {
    const_iterator it(v.begin());
    for (auto& i : m_component) {
        i -= *it;
        ++it;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator*=(const Matrix<T,N,M>& v) {
    const_iterator it(v.begin());
    for (auto& i : m_component) {
        i *= *it;
        ++it;
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator/=(const Matrix<T,N,M>& v) {
    const_iterator it(v.begin());
    for (auto& i : m_component) {
        i /= *it;
        ++it;
    }
    return *this;
}


}