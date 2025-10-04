#pragma once

#include <cmath>
#include <array>

#include "BaseVector.hpp"
#include "Complex.hpp"
#include "Vector.hpp"

namespace mat {

template<typename T, uint32_t N>
class Vector;

/*
Rule :
i2 = j2 = k2 = ijk = -1

ij =  k, jk =  i, ki =  j
ji = -k, kj = -i, ik = -j

For rotations :
Axis of rotation is the imaginary vector
*/

//     ___ _            
//    / __| |__ _ ______
//   | (__| / _` (_-<_-<
//    \___|_\__,_/__/__/
//                      

template<typename T>
class Quaternion : public BaseVector<T,4> {
public:
    // === Base Vector using ===
    
    using typename BaseVector<T, 4>::iterator; 
    using typename BaseVector<T, 4>::const_iterator;
    using BaseVector<T, 4>::m_component;

public:

//     ___             _               _           
//    / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ 
//   | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
//    \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|  
//                                                 

    /// @brief Default constructor, quaternion is zero
    Quaternion();

    /// @brief Constructor, quaternion is equal to a real number
    /// @param real The real number
    Quaternion(T real);

    /// @brief Constructor, use a real part (scalar) and an imaginary part (vector 3)
    /// @param real Real part (scalar)
    /// @param imag Imaginary part (vector 3)
    Quaternion(T real, const Vector<T,3>& imag);

    /// @brief Constructor, use a real part (scalar) and an imaginary part (array 3)
    /// @param real Real part (scalar)
    /// @param imag Imaginary part (array 3)
    Quaternion(T real, const std::array<T,3>& imag);

    /// @brief Constructor, fill each component real, i, j, k
    /// @param real Real component
    /// @param i i component
    /// @param j j component
    /// @param k k component
    Quaternion(T real, T i, T j, T k);

    /// @brief Constructor, use an initial array 4
    /// @param init_array Initial array
    Quaternion(const std::array<T,4>& init_array);

    /// @brief Constructor, use an initializer list
    /// @param init_list Initializer list
    Quaternion(const std::initializer_list<T>& init_list);

//    __  __     _   _            _    
//   |  \/  |___| |_| |_  ___  __| |___
//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
//   |_|  |_\___|\__|_||_\___/\__,_/__/
//                                     

    // === Utils ===

    /// @brief Get a reference to the real part
    /// @return A reference to the real part
    T& r();

    /// @brief Get a reference to the i part
    /// @return A reference to the i part
    T& i();

    /// @brief Get a reference to the j part
    /// @return A reference to the j part
    T& j();

    /// @brief Get a reference to the k part
    /// @return A reference to the k part
    T& k();

    /// @brief Get a constant reference to the real part
    /// @return A constant reference to the real part
    const T& r() const;

    /// @brief Get a constant reference to the i part
    /// @return A constant reference to the i part
    const T& i() const;

    /// @brief Get a constant reference to the j part
    /// @return A constant reference to the j part
    const T& j() const;

    /// @brief Get a constant reference to the k part
    /// @return A constant reference to the k part
    const T& k() const;

    /// @brief Compute the square of the norm
    /// @return The square of the norm
    T norm2() const;

    /// @brief Compute the norm
    /// @return The norm
    T norm() const;

    /// @brief Normalize the quaternion
    void normalize();

    /// @brief Conjugate the quaternion
    void conjugate();

    /// @brief Get a copy of the real component
    /// @return A copy of the real component
    T real() const;

    /// @brief Get a copy of the imaginary components
    /// @return A vector 3 of the imaginary components
    Vector<T,3> imag() const;

//     ___                     _              
//    / _ \ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | (_) | '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//    \___/| .__/\___|_| \__,_|\__\___/_| /__/
//         |_|                                

    // === Cast operators ===

    /// @brief Cast to a base vector
    operator BaseVector<T,4>&();

    // === Operators ===

    /// @brief Add a real number
    /// @param a The real number
    /// @return Reference to quaternion
    Quaternion& operator+=(T a);

    /// @brief Substract a real number
    /// @param a The real number
    /// @return Reference to quaternion
    Quaternion& operator-=(T a);

    /// @brief Multiply the quaternion by a real number
    /// @param a The real number
    /// @return Reference to quaternion
    Quaternion& operator*=(T a);

    /// @brief Divide the quaternion by a real number
    /// @param a The real number
    /// @return Reference to quaternion
    Quaternion& operator/=(T a);

    /// @brief Add a quaternion
    /// @param q The quaternion
    /// @return Reference to quaternion
    Quaternion& operator+=(const Quaternion<T>& q);

    /// @brief Substract a quaternion
    /// @param q The quaternion
    /// @return Reference to quaternion
    Quaternion& operator-=(const Quaternion<T>& q);

    /// @brief Multiply a quaternion
    /// @param q The quaternion
    /// @return Reference to quaternion
    Quaternion& operator*=(const Quaternion<T>& q);
};


// ===================================================================================================
// ===================================================================================================


//    ___       __ _      _ _   _             
//   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  ___
//   | |) / -_)  _| | ' \| |  _| / _ \ ' \(_-<
//   |___/\___|_| |_|_||_|_|\__|_\___/_||_/__/
//                                            


template<typename T>
Quaternion<T>::Quaternion() 
: BaseVector<T, 4>()
{}

template<typename T>
Quaternion<T>::Quaternion(T real)
: BaseVector<T, 4>{real, T(0), T(0), T(0)}
{}

template<typename T>
Quaternion<T>::Quaternion(T real, const Vector<T,3>& imag)
: BaseVector<T, 4>{real, imag[0], imag[1], imag[2]}
{}

template<typename T>
Quaternion<T>::Quaternion(T real, const std::array<T,3>& imag)
: BaseVector<T, 4>{real, imag[0], imag[1], imag[2]}
{}

template<typename T>
Quaternion<T>::Quaternion(T real, T i, T j, T k)
: BaseVector<T, 4>{real, i, j, k}
{}

template<typename T>
Quaternion<T>::Quaternion(const std::array<T,4>& init_array)
: BaseVector<T, 4>(init_array)
{}

template<typename T>
Quaternion<T>::Quaternion(const std::initializer_list<T>& init_list)
: BaseVector<T, 4>(init_list)
{}

template<typename T>
T& Quaternion<T>::r() { 
    return m_component[0]; 
}

template<typename T>
T& Quaternion<T>::i() { 
    return m_component[1]; 
}

template<typename T>
T& Quaternion<T>::j() { 
    return m_component[2]; 
}

template<typename T>
T& Quaternion<T>::k() { 
    return m_component[3]; 
}

template<typename T>
const T& Quaternion<T>::r() const { 
    return m_component[0]; 
}

template<typename T>
const T& Quaternion<T>::i() const { 
    return m_component[1]; 
}

template<typename T>
const T& Quaternion<T>::j() const { 
    return m_component[2]; 
}

template<typename T>
const T& Quaternion<T>::k() const { 
    return m_component[3]; 
}

template<typename T>
T Quaternion<T>::norm2() const { 
    return m_component[0]*m_component[0] + m_component[1]*m_component[1] + 
        m_component[2]*m_component[2] + m_component[3]*m_component[3]; 
}

template<typename T>
T Quaternion<T>::norm() const { 
    return sqrt(norm2()); 
}

template<typename T>
void Quaternion<T>::normalize() {
    T n = norm();
    m_component[0] /= n;
    m_component[1] /= n;
    m_component[2] /= n;
    m_component[3] /= n;
}

template<typename T>
void Quaternion<T>::conjugate() {
    m_component[1] = -m_component[1];
    m_component[2] = -m_component[2];
    m_component[3] = -m_component[3];
}

template<typename T>
T Quaternion<T>::real() const { 
    return m_component[0]; 
}

template<typename T>
Vector<T,3> Quaternion<T>::imag() const { 
    return Vector<T,3>(std::array<T,3>{m_component[1], m_component[2], m_component[3]}); 
}

template<typename T>
Quaternion<T>::operator BaseVector<T,4>&() {
    return *reinterpret_cast<BaseVector<T,4>*>(this);
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator+=(T a) {
    m_component[0] += a;
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator-=(T a) {
    m_component[0] -= a;
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator*=(T a) { 
    m_component[0] *= a;
    m_component[1] *= a;
    m_component[2] *= a;
    m_component[3] *= a;
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator/=(T a) { 
    m_component[0] /= a;
    m_component[1] /= a;
    m_component[2] /= a;
    m_component[3] /= a; 
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& q) { 
    m_component[0] += q.r();
    m_component[1] += q.i();
    m_component[2] += q.j();
    m_component[3] += q.k(); 
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& q) { 
    m_component[0] -= q.r();
    m_component[1] -= q.i();
    m_component[2] -= q.j();
    m_component[3] -= q.k();
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& q) { 
    T r_ = m_component[0]*q.r() - m_component[1]*q.i() - m_component[2]*q.j() - m_component[3]*q.k();
    T i_ = m_component[0]*q.i() + m_component[1]*q.r() + m_component[2]*q.k() - m_component[3]*q.j();
    T j_ = m_component[0]*q.j() + m_component[2]*q.r() + m_component[3]*q.i() - m_component[1]*q.k();
    T k_ = m_component[0]*q.k() + m_component[3]*q.r() + m_component[1]*q.j() - m_component[2]*q.i();
    m_component[0] = r_;
    m_component[1] = i_;
    m_component[2] = j_;
    m_component[3] = k_;
    return *this;
}

}