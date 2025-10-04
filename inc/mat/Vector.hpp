#pragma once

#include <inttypes.h>
#include <vector>
#include <array>
#include <list>
#include <ostream>
#include <cmath>

#include "BaseVector.hpp"
#include "Complex.hpp"

namespace mat {

//     ___ _            
//    / __| |__ _ ______
//   | (__| / _` (_-<_-<
//    \___|_\__,_/__/__/
//                      

/// @brief Mathematical vector
/// @tparam T Type of the vector
/// @tparam N Size of the vector
template<typename T, uint32_t N>
class Vector : public BaseVector<T,N> {

public:
    // === Base Vector using ===
    
    using typename BaseVector<T, N>::iterator; 
    using typename BaseVector<T, N>::const_iterator;
    using BaseVector<T, N>::m_component;

public:

//     ___             _               _           
//    / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ 
//   | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
//    \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|  
//                                                 

    /// @brief Default constructor, fill the vector with value 0
    Vector();

    /// @brief Constructor, fill the vector with a value
    /// @param fill_val Value that fill the vector
    Vector(T fill_val);

    /// @brief Constructor, copy an array
    /// @param init_array Initial array
    Vector(const std::array<T,N>& init_array);

    /// @brief Constructor, copy an initializer list
    /// @param init_list Initializer list
    Vector(const std::initializer_list<T>& init_list);

//    __  __     _   _            _    
//   |  \/  |___| |_| |_  ___  __| |___
//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
//   |_|  |_\___|\__|_||_\___/\__,_/__/
//                                     

    /// @brief Compute the square of the norm
    /// @return The square of the norm
    T norm2() const;

    /// @brief Compute the the norm
    /// @return The norm
    T norm() const;

    /// @brief Normalize the vector
    void normalize();

//     ___                     _              
//    / _ \ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | (_) | '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//    \___/| .__/\___|_| \__,_|\__\___/_| /__/
//         |_|                                

    // === Cast operator ===

    /// @brief Cast to a base vector
    operator BaseVector<T,N>&();

    // === internal operators ===

    /// @brief Sum each vector element with a scalar
    /// @param a Scalar
    /// @return Reference to the vector
    Vector& operator+=(T a);

    /// @brief Subtract each vector element with a scalar
    /// @param a Scalar
    /// @return Reference to the vector
    Vector& operator-=(T a);

    /// @brief Multiply each vector element with a scalar
    /// @param a Scalar
    /// @return Reference to the vector
    Vector& operator*=(T a);

    /// @brief Divide each vector element with a scalar
    /// @param a Scalar
    /// @return Reference to the vector
    Vector& operator/=(T a);

    /// @brief Add two vectors
    /// @param v Vector
    /// @return Reference to the vector
    Vector& operator+=(const Vector<T,N>& v);

    /// @brief Substract two vectors
    /// @param v Vector
    /// @return Reference to the vector
    Vector& operator-=(const Vector<T,N>& v);

    /// @brief Multiply each element of the two vectors
    /// @param v Vector
    /// @return Reference to the vector
    /// @warning It is not a dot product, use the function dot
    Vector& operator*=(const Vector<T,N>& v);

    /// @brief Divide each element of the two vectors
    /// @param v Vector
    /// @return Reference to the vector
    Vector& operator/=(const Vector<T,N>& v);
};


// ===================================================================================================
// ===================================================================================================


//    ___       __ _      _ _   _             
//   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  ___
//   | |) / -_)  _| | ' \| |  _| / _ \ ' \(_-<
//   |___/\___|_| |_|_||_|_|\__|_\___/_||_/__/
//                                            

template<typename T, uint32_t N>
Vector<T,N>::Vector() 
: BaseVector<T,N>()
{}

template<typename T, uint32_t N>
Vector<T,N>::Vector(T fill_val) 
: BaseVector<T,N>()
{
    m_component.fill(fill_val);
}

template<typename T, uint32_t N>
Vector<T,N>::Vector(const std::array<T,N>& init_array)
: BaseVector<T,N>(init_array)
{}

template<typename T, uint32_t N>
Vector<T,N>::Vector(const std::initializer_list<T>& init_list)
: BaseVector<T,N>(init_list)
{}

template<typename T, uint32_t N>
T Vector<T,N>::norm2() const {
    T result(0);
    for (auto i : m_component) {
        result += i * i;
    }
    return result;
}

template<typename T, uint32_t N>
T Vector<T,N>::norm() const {
    return sqrt(norm2()); 
}

template<typename T, uint32_t N>
void Vector<T,N>::normalize() {
    T n = norm();
    for (auto& i : m_component) {
        i /= n;
    }
}

template<typename T, uint32_t N>
Vector<T,N>::operator BaseVector<T,N>&() {
    return *reinterpret_cast<BaseVector<T,N>*>(this);
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator+=(T a) {
    for (auto& i : m_component) {
        i += a;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator-=(T a) {
    for (auto& i : m_component) {
        i -= a;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator*=(T a) {
    for (auto& i : m_component) {
        i *= a;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator/=(T a) {
    for (auto& i : m_component) {
        i /= a;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator+=(const Vector<T,N>& v) {
    const_iterator it = v.begin();
    for (auto& i : m_component) {
        i += *it;
        ++it;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator-=(const Vector<T,N>& v) {
    const_iterator it = v.begin();
    for (auto& i : m_component) {
        i -= *it;
        ++it;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator*=(const Vector<T,N>& v) {
    const_iterator it = v.begin();
    for (auto& i : m_component) {
        i *= *it;
        ++it;
    }
    return *this;
}

template<typename T, uint32_t N>
Vector<T,N>& Vector<T,N>::operator/=(const Vector<T,N>& v)  {
    const_iterator it = v.begin();
    for (auto& i : m_component) {
        i /= *it;
        ++it;
    }
    return *this;
}

}