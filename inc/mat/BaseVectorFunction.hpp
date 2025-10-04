#pragma once

#include <ostream>

#include "BaseVector.hpp"

namespace mat {

//    ___     _                     _ 
//   | __|_ _| |_ ___ _ _ _ _  __ _| |
//   | _|\ \ /  _/ -_) '_| ' \/ _` | |
//   |___/_\_\\__\___|_| |_||_\__,_|_|
//                                    

/// @brief Stream operator, write the vector into a stream
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param stream The stream
/// @param v The vector
/// @return The stream with the modifications
template<typename T, uint32_t N>
std::ostream& operator<<(std::ostream& stream, const BaseVector<T,N>& v) {
    stream << "(";
    for (uint32_t i(0) ; i < N ; ++i) {
        stream << v[i];
        i != N-1 ? stream << ", " : stream << ")" ;
    }

    return stream;
}

/// @brief Cast a vector of type 1 to another vector of type 2
/// @tparam T1 Current type
/// @tparam T2 New type
/// @tparam N Size of vector
/// @param v The current vector
/// @return The vector of the new type
template<typename T1, typename T2, uint32_t N>
BaseVector<T2,N> cast(const BaseVector<T1,N>& v) {
    BaseVector<T2,N> result;
    T2* it = result.begin();
    for (auto i : v) {
        *it = (T1)i;
        ++it;
    }
    return result;
}

/// @brief Get the minimum value of a vector
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v The vector
/// @return The smallest component
template<typename T, uint32_t N>
T min(const BaseVector<T,N>& v) {
    T m = v[0];
    for (auto i : v) {
        if (i < m){
            m = i;
        }
    }
    return m;
}

/// @brief Get the minimum between components and a scalar
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v The vector
/// @param a The scalar
/// @return A vector with minimum between the component and the scalar
template<typename T, uint32_t N>
BaseVector<T,N> min(BaseVector<T,N> v, T a) {
    for (auto& i : v) {
        if (a < i) {
            i = a;
        }
    }
    return v;
}

/// @brief Get the minimum for each components of two vectors
/// @tparam T Type of vectors
/// @tparam N Size of vectors
/// @param v1 First vector
/// @param v2 Second vector
/// @return A vector containing the smallest values between the components of the two vectors
template<typename T, uint32_t N>
BaseVector<T,N> min(BaseVector<T,N> v1, const BaseVector<T,N>& v2) {
    for (uint32_t i(0) ; i < N ; ++i) {
        if (v2[i] < v1[i]) {
            v1[i] = v2[i];
        }
    }
    return v1;
}

/// @brief Get the maximum value of a vector
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v The vector
/// @return The biggest component
template<typename T, uint32_t N>
T max(const BaseVector<T,N>& v) {
    T m = v[0];
    for (auto i : v) {
        if (i > m){
            m = i;
        }
    }
    return m;
}

/// @brief Get the maximum between components and a scalar
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v The vector
/// @param a The scalar
/// @return A vector with maximum between the component and the scalar
template<typename T, uint32_t N>
BaseVector<T,N> max(BaseVector<T,N> v, T a) {
    for (auto& i : v) {
        if (a > i) {
            i = a;
        }
    }
    return v;
}

/// @brief Get the maximum for each components of two vectors
/// @tparam T Type of vectors
/// @tparam N Size of vectors
/// @param v1 First vector
/// @param v2 Second vector
/// @return A vector containing the biggest values between the components of the two vectors
template<typename T, uint32_t N>
BaseVector<T,N> max(BaseVector<T,N> v1, const BaseVector<T,N>& v2) {
    for (uint32_t i(0) ; i < N ; ++i) {
        if (v2[i] > v1[i]) {
            v1[i] = v2[i];
        }
    }
    return v1;
}

/// @brief Return a vector with absolute components
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v The vector
/// @return The vector with absolute component
template<typename T, uint32_t N>
BaseVector<T,N> abs(const BaseVector<T,N>& v) {
    BaseVector<T,N> result;
    T* it = result.begin();
    T zero(0);
    for (auto i : v) {
        i < zero ? *it = -i : *it = i;
        ++it;
    }
    return result;
}

/// @brief Return a vector of +1 or -1 whether the component is > 0 or < 0
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v The vector
/// @return A vector of the sign of the components
template<typename T, uint32_t N>
BaseVector<T,N> sign(BaseVector<T,N> v) {
    T zero(0);
    T mone(-1);
    T one(1);
    for (auto& i : v) {
        if (i < zero) {
            i = mone;
        }else if(i > zero) {
            i = one;
        }else{
            i = zero;
        }
    }
    return v;
}

}