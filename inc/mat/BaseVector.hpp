#pragma once

#include <array>
#include <inttypes.h>

#include "Vector.hpp"
#include "Complex.hpp"
#include "Quaternion.hpp"

namespace mat {

template<typename T, uint32_t N>
class Vector;

template<typename T>
class Complex;

template<typename T>
class Quaternion;

//     ___ _            
//    / __| |__ _ ______
//   | (__| / _` (_-<_-<
//    \___|_\__,_/__/__/
//                      

/// @brief Class that represent a vector without any operations
/// @tparam T Type of vector
/// @tparam N Dimension of the vector
template<typename T, uint32_t N>
class BaseVector {
public:
    // === Define iterators ===

    typedef T* iterator;
    typedef const T* const_iterator;

public:

//     ___             _               _           
//    / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ 
//   | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
//    \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|  
//                                                 

    /// @brief Default constructor (fill with 0)
    BaseVector();

    /// @brief Constructor with an array
    /// @param init_array Array of the components
    BaseVector(const std::array<T,N>& init_array);

    /// @brief Constructor with an initializer list
    /// @param init_list Initializer list containing the components
    BaseVector(const std::initializer_list<T>& init_list);

//    __  __     _   _            _    
//   |  \/  |___| |_| |_  ___  __| |___
//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
//   |_|  |_\___|\__|_||_\___/\__,_/__/
//                                     

    // === Utils ===

    /// @brief Get a constant reference to the array of components
    /// @return A constant reference to the array of components
    const std::array<T,N>& data() const;

    /// @brief Get the size (dimension) of the vector
    /// @return The size (dimension) of the vector
    uint32_t size() const;

    /// @brief Copy data into the vector
    /// @param start A pointer to the first element that will be copy
    void copy(T* start);

    // === Iterators methods ===

    /// @brief Get the begin iterator
    /// @return The begin iterator
    iterator begin();

    /// @brief Get the constant begin iterator
    /// @return The constant begin iterator
    const_iterator begin() const;

    /// @brief Get the end iterator
    /// @return The end iterator
    iterator end();

    /// @brief Get the constant end iterator
    /// @return The constant end iterator
    const_iterator end() const;

//     ___                     _              
//    / _ \ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | (_) | '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//    \___/| .__/\___|_| \__,_|\__\___/_| /__/
//         |_|                                

    // === Accessor operators ===

    /// @brief Constant accessor operator
    /// @param index Index of the element
    /// @return A constant reference to the element
    const T& operator[](uint32_t index) const;

    /// @brief Accessor operator
    /// @param index Index of the element
    /// @return A reference to the element
    T& operator[](uint32_t index);

    // === Comparison operators ===

    /// @brief Is equal operator (true if all components are equal)
    /// @param v The vector that will be compared
    /// @return If the vectors are equal
    bool operator==(const BaseVector<T,N>& v) const;

    /// @brief Is different operator (true if at least one component is different)
    /// @param v The vector that will be compared
    /// @return If the vectors are different
    bool operator!=(const BaseVector<T,N>& v) const;

    // === Cast operator ===

    /// @brief Cast to a vector
    operator Vector<T,N>&();

    /// @brief Cast to a complex
    /// @warning Only if N = 2
    operator Complex<T>&();

    /// @brief Cast to a quaternion
    /// @warning Only if N = 4
    operator Quaternion<T>&();

protected:
    // Components of the vector
    std::array<T,N> m_component;
};


// ===================================================================================================
// ===================================================================================================


//    ___       __ _      _ _   _             
//   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  ___
//   | |) / -_)  _| | ' \| |  _| / _ \ ' \(_-<
//   |___/\___|_| |_|_||_|_|\__|_\___/_||_/__/
//                                            

template<typename T, uint32_t N>
BaseVector<T,N>::BaseVector() {
    m_component.fill(T(0));
}

template<typename T, uint32_t N>
BaseVector<T,N>::BaseVector(const std::array<T,N>& init_array)
: m_component(init_array)
{}

template<typename T, uint32_t N>
BaseVector<T,N>::BaseVector(const std::initializer_list<T>& init_list) {
    m_component.fill(T(0));
    uint32_t last = std::min((size_t)N, init_list.size());
    std::copy(init_list.begin(), init_list.begin()+last, m_component.begin());
}

template<typename T, uint32_t N>
const std::array<T,N>& BaseVector<T,N>::data() const {
    return m_component;
}

template<typename T, uint32_t N>
uint32_t BaseVector<T,N>::size() const {
    return N;
}

template<typename T, uint32_t N>
void BaseVector<T,N>::copy(T* start) {
    std::copy(start, start+N, m_component.begin());
}

template<typename T, uint32_t N>
const T& BaseVector<T,N>::operator[](uint32_t index) const {
    return m_component[index];
}

template<typename T, uint32_t N>
T& BaseVector<T,N>::operator[](uint32_t index) {
    return m_component[index];
}

template<typename T, uint32_t N>
bool BaseVector<T,N>::operator==(const BaseVector<T,N>& v) const {
    const_iterator it = v.begin();
    for (auto i : m_component) {
        if (i != *it) {
            return false;
        }
        ++it;
    }
    return true;
}

template<typename T, uint32_t N>
bool BaseVector<T,N>::operator!=(const BaseVector<T,N>& v) const {
    return !(*this == v);
}

template<typename T, uint32_t N>
BaseVector<T,N>::operator Vector<T,N>&() {
    return *reinterpret_cast<Vector<T,N>*>(this);
}

template<typename T, uint32_t N>
BaseVector<T,N>::operator Complex<T>&() {
    static_assert(N == 2, "Error : can create a Complex only from Vector of dimension 2");
    return *reinterpret_cast<Complex<T>*>(this);
}

template<typename T, uint32_t N>
BaseVector<T,N>::operator Quaternion<T>&() {
    static_assert(N == 4, "Error : can create a Quaternion only from Vector of dimension 4");
    return *reinterpret_cast<Quaternion<T>*>(this);
}

template<typename T, uint32_t N>
T* BaseVector<T,N>::begin() {
    return &m_component[0];
}

template<typename T, uint32_t N>
const T* BaseVector<T,N>::begin() const {
    return &m_component[0];
}

template<typename T, uint32_t N>
T* BaseVector<T,N>::end() {
    return &m_component[0] + N;
}

template<typename T, uint32_t N>
const T* BaseVector<T,N>::end() const {
    return &m_component[0] + N;
}

}