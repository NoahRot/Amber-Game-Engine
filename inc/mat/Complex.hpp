#pragma once

#include <iostream>
#include <cmath>

#include "BaseVector.hpp"
#include "Vector.hpp"

namespace mat {

template<typename T, uint32_t N>
class BaseVector;

template<typename T, uint32_t N>
class Vector;

//     ___ _            
//    / __| |__ _ ______
//   | (__| / _` (_-<_-<
//    \___|_\__,_/__/__/
//                      

template<typename T>
class Complex : public BaseVector<T,2> {
public:
    // === Base Vector using ===
    
    using typename BaseVector<T, 2>::iterator; 
    using typename BaseVector<T, 2>::const_iterator;
    using BaseVector<T, 2>::m_component;


public:

//     ___             _               _           
//    / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ 
//   | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
//    \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|  
//                                                 

    /// @brief Default constructor, fill the vector with value 0
    Complex();

    /// @brief Constructor with only a real part
    /// @param re Real part
    Complex(T re);

    /// @brief Constructor with a real and an imaginary part
    /// @param re Real part
    /// @param im Imaginary part
    Complex(T re, T im);

    /// @brief Constructor, copy an array
    /// @param init_array Initial array
    Complex(const std::array<T,2>& init_array);

    /// @brief Constructor, copy an initializer list
    /// @param init_list Initializer list
    Complex(const std::initializer_list<T>& init_list);

//    __  __     _   _            _    
//   |  \/  |___| |_| |_  ___  __| |___
//   | |\/| / -_)  _| ' \/ _ \/ _` (_-<
//   |_|  |_\___|\__|_||_\___/\__,_/__/
//                                     

    /// @brief Get the real part
    /// @return A reference to the real part
    T& real();

    /// @brief Get the imaginary part
    /// @return A reference to the imaginary part
    T& imag();

    /// @brief Get the real part
    /// @return A constant reference to the real part
    const T& real() const;

    /// @brief Get the imaginary part
    /// @return A constant reference to the imaginary part
    const T& imag() const;

    /// @brief Compute the square modulus
    /// @return The square modulus
    T modulus2() const;

    /// @brief Compute the modulus
    /// @return The modulus
    T modulus() const;

    /// @brief Compute the argument
    /// @return The argument
    T argument() const;

    /// @brief Conjugate the complex
    void conjugate();

    /// @brief Normalize the complex
    void normalize();

    /// @brief Set the component from a polar form
    /// @param mod The modulus of the complex
    /// @param argu The argument of the complex
    void set_polar(T mod, T argu);

    /// @brief Get the component from a polar form
    /// @param mod A reference to the modulus of the complex
    /// @param argu A reference to the argument of the complex
    void get_polar(T& magn, T& argu);

//     ___                     _              
//    / _ \ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | (_) | '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//    \___/| .__/\___|_| \__,_|\__\___/_| /__/
//         |_|                                

    // === Cast operators ===

    /// @brief Cast to a base vector
    operator BaseVector<T,2>&();

    // === Operators ===
    
    /// @brief Add a real number
    /// @param a The real number
    /// @return Reference to the complex
    Complex& operator+=(T a);

    /// @brief Substract a real number
    /// @param a The real number 
    /// @return Reference to the complex
    Complex& operator-=(T a);

    /// @brief Multiply by a real number
    /// @param a The real number 
    /// @return Reference to the complex
    Complex& operator*=(T a);

    /// @brief Divide by a real number
    /// @param a The real number 
    /// @return Reference to the complex
    Complex& operator/=(T a);

    /// @brief Add two complex
    /// @param c Complex
    /// @return Reference to the complex
    Complex& operator+=(const Complex<T>& c);

    /// @brief Substract two complex
    /// @param c Complex
    /// @return Reference to the complex
    Complex& operator-=(const Complex<T>& c);

    /// @brief Multiply two complex
    /// @param c Complex
    /// @return Reference to the complex
    Complex& operator*=(const Complex<T>& c);

    /// @brief Divide two complex
    /// @param c Complex
    /// @return Reference to the complex
    Complex& operator/=(const Complex<T>& c);
};


// ===================================================================================================
// ===================================================================================================


//    ___       __ _      _ _   _             
//   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  ___
//   | |) / -_)  _| | ' \| |  _| / _ \ ' \(_-<
//   |___/\___|_| |_|_||_|_|\__|_\___/_||_/__/
//                                            

template<typename T>
Complex<T>::Complex()
: BaseVector<T,2>()
{}

template<typename T>
Complex<T>::Complex(T re)
: BaseVector<T,2>{re}
{}

template<typename T>
Complex<T>::Complex(T re, T im)
: BaseVector<T,2>{re, im}
{}

template<typename T>
Complex<T>::Complex(const std::array<T,2>& init_array) 
: BaseVector<T,2>(init_array)
{}

template<typename T>
Complex<T>::Complex(const std::initializer_list<T>& init_list) 
: BaseVector<T,2>(init_list)
{}

template<typename T>
T& Complex<T>::real() { 
    return m_component[0]; 
}

template<typename T>
T& Complex<T>::imag() { 
    return m_component[1]; 
}

template<typename T>
const T& Complex<T>::real() const { 
    return m_component[0]; 
}

template<typename T>
const T& Complex<T>::imag() const { 
    return m_component[1]; 
}

template<typename T>
T Complex<T>::modulus2() const { 
    return m_component[0] * m_component[0] + m_component[1] * m_component[1]; 
}

template<typename T>
T Complex<T>::modulus() const { 
    return sqrt(modulus2()); 
}

template<typename T>
T Complex<T>::argument() const { 
    return atan2(m_component[1], m_component[0]); 
}

template<typename T>
void Complex<T>::conjugate() { 
    m_component[1] = -m_component[1]; 
}

template<typename T>
void Complex<T>::normalize() {
    T m = modulus();
    m_component[0] /= m;
    m_component[1] /= m;
}

template<typename T>
void Complex<T>::set_polar(T magn, T argu) { 
    m_component[0] = magn * cos(argu); 
    m_component[1] = magn * sin(argu); 
}

template<typename T>
void Complex<T>::get_polar(T& magn, T& argu) { 
    magn = modulus(); 
    argu = argument(); 
}

template<typename T>
Complex<T>::operator BaseVector<T,2>&() {
    return *reinterpret_cast<BaseVector<T,2>*>(this);
}

template<typename T>
Complex<T>& Complex<T>::operator+=(T a) {
    m_component[0] += a;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator-=(T a) {
    m_component[0] -= a;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator*=(T a) { 
    m_component[0] *= a;
    m_component[1] *= a;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator/=(T a) { 
    m_component[0] /= a; 
    m_component[1] /= a; 
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator+=(const Complex<T>& c) { 
    m_component[0] += c.real();
    m_component[1] += c.imag();
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator-=(const Complex<T>& c) { 
    m_component[0] -= c.real();
    m_component[1] -= c.imag();
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator*=(const Complex<T>& c) { 
    T r = m_component[0] * c.real() - m_component[1] * c.imag();
    T i = m_component[0] * c.imag() + m_component[1] * c.real();
    m_component[0] = r;
    m_component[1] = i;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator/=(const Complex<T>& c) { 
    T r = (m_component[0]*c.real() + m_component[1]*c.imag()) / c.modulus2();
    T i = (m_component[1]*c.real() - m_component[0]*c.imag()) / c.modulus2();
    m_component[0] = r;
    m_component[1] = i;
    return *this;
}

}