#pragma once

#include "Complex.hpp"
#include "Matrix.hpp"

namespace mat {

//    ___     _                     _                          _              
//   | __|_ _| |_ ___ _ _ _ _  __ _| |  ___ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | _|\ \ /  _/ -_) '_| ' \/ _` | | / _ \ '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//   |___/_\_\\__\___|_| |_||_\__,_|_| \___/ .__/\___|_| \__,_|\__\___/_| /__/
//                                         |_|                                

/// @brief Stream operator, write the complex into a stream
/// @tparam T The type of complex
/// @param stream The stream
/// @param c The complex
/// @return The stream with the modifications
template<typename T>
std::ostream& operator<<(std::ostream& stream, const Complex<T>& c) {
    stream << "Com(" << c.real() << " + " << c.imag() << "i)";
    return stream;
}

/// @brief Add a real number to a complex
/// @tparam T The type of complex
/// @param c The complex
/// @param a The real number
/// @return The new complex
template<typename T>
Complex<T> operator+(Complex<T> c, T a) {
    return c += a;
}

/// @brief Add a real number to a complex
/// @tparam T The type of complex
/// @param a The real number
/// @param c The complex
/// @return The new complex
template<typename T>
Complex<T> operator+(T a, Complex<T> c) {
    return c += a;
}

/// @brief Substract a real number to a complex
/// @tparam T The type of complex
/// @param c The complex
/// @param a The real number
/// @return The new complex
template<typename T>
Complex<T> operator-(Complex<T> c, T a) {
    return c -= a;
}

/// @brief Substract a complex to a real number
/// @tparam T The type of complex
/// @param a The real number
/// @param c The complex
/// @return The new complex
template<typename T>
Complex<T> operator-(T a, Complex<T> c) {
    return -c += a;
}

/// @brief Multiply a complex by a real number
/// @tparam T The type of complex
/// @param c The complex
/// @param a The real number
/// @return The new complex
template<typename T>
Complex<T> operator*(Complex<T> c, T a) {
    return c *= a;
}

/// @brief Multiply a complex by a real number
/// @tparam T The type of complex
/// @param a The real number
/// @param c The complex
/// @return The new complex
template<typename T>
Complex<T> operator*(T a, Complex<T> c) {
    return c *= a;
}

/// @brief Divide a complex by a real number
/// @tparam T The type of complex
/// @param c The complex
/// @param a The real number
/// @return The newcomplex
template<typename T>
Complex<T> operator/(Complex<T> c, T a) {
    return c /= a;
}

/// @brief Divide a real number by a complex
/// @tparam T The type of complex
/// @param a The real number
/// @param c The complex
/// @return The new complex
template<typename T>
Complex<T> operator/(T a, const Complex<T>& c) {
    return Complex<T>(a*c.real() / c.modulus2(), -a*c.imag() / c.modulus2());
}

/// @brief Addition of two complex
/// @tparam T The type of complex
/// @param c1 First complex
/// @param c2 Second complex
/// @return The addition of the two complex
template<typename T>
Complex<T> operator+(Complex<T> c1, const Complex<T>& c2) {
    return c1 += c2;
}

/// @brief Substraction of two complex
/// @tparam T The type of complex
/// @param c1 First complex
/// @param c2 Second complex
/// @return The substraction of the two complex
template<typename T>
Complex<T> operator-(Complex<T> c1, const Complex<T>& c2) {
    return c1 -= c2;
}

/// @brief Multiplication of two complex
/// @tparam T The type of complex
/// @param c1 First complex
/// @param c2 Second complex
/// @return The multiplication of the two complex
template<typename T>
Complex<T> operator*(Complex<T> c1, const Complex<T>& c2) {
    return c1 *= c2;
}

/// @brief Division of two complex
/// @tparam T The type of complex
/// @param c1 First complex
/// @param c2 Second complex
/// @return The division of the two complex
template<typename T>
Complex<T> operator/(Complex<T> c1, const Complex<T>& c2) {
    return c1 /= c2;
}

/// @brief Multiply the complex by -1
/// @tparam T The type of complex
/// @param c The complex
/// @return Minus the complex (-z)
template<typename T>
Complex<T> operator-(const Complex<T>& c) {
    return Complex<T>{-c.real(), -c.imag()};
}

//    ___             _   _             
//   | __|  _ _ _  __| |_(_)___ _ _  ___
//   | _| || | ' \/ _|  _| / _ \ ' \(_-<
//   |_| \_,_|_||_\__|\__|_\___/_||_/__/
//                                      

/// @brief Compute the rotation matrix from a complex
/// @tparam T The type of complex
/// @param c The complex
/// @return The rotation matrix
template<typename T>
Matrix<T,2,2> complex_to_rotation_matrix(const Complex<T>& c) {
    T co = c.real() / c.modulus();
    T si = c.imag() / c.modulus();
    return Matrix<T,2,2>(std::array<T,4>{co, si, -si, co});
}

/// @brief Compute the complex associate to a rotation of an angle
/// @tparam T The type of complex
/// @param angle The angle of rotation
/// @return The complex
template<typename T>
Complex<T> angle_to_complex(T angle) {
    return Complex<T>(cos(angle), sin(angle));
}

/// @brief Rotate a vector using a complex as rotation
/// @tparam T Type of complex
/// @param c The type complex
/// @param v The vector
/// @return The rotated vector
template<typename T>
Vector<T,2> complex_rotate_vec(const Complex<T>& c, Vector<T,2> v) {
    return (Vector<T,2>)(c * (Complex<T>)v);
}

/// @brief Compute the conjugate of a complex
/// @tparam T The type of complex
/// @param c The complex
/// @return The conjugate of the complex
template<typename T>
Complex<T> conjugate(Complex<T> c) {
    return c.conjugate();
}

/// @brief Compute the conjugate of a complex matrix
/// @tparam T The type of complex
/// @tparam N Row of the matrix
/// @tparam M Column of the matrix
/// @param m The complex matrix
/// @return The conjugate of the matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<Complex<T>, N, M> conjugate(Matrix<Complex<T>, N, M> m) {
    for (Complex<T>& i : m) {
        i.conjugate();
    }
    return m;
}

/// @brief Conjugate a complex matrix
/// @tparam T Type of complex
/// @tparam N Row of the matrix
/// @tparam M Column of the matrix
/// @param m The complex matrix
template<typename T, uint32_t N, uint32_t M>
void self_conjugate(Matrix<Complex<T>, N, M>& m) {
    for (Complex<T>& i : m) {
        i.conjugate();
    }
}

/// @brief Compute the conjugate transpose of a complex matrix
/// @tparam T The type of complex
/// @tparam N Row of the matrix
/// @tparam M Column of the matrix
/// @param m The complex matrix
/// @return The conjugate transpose of the complex matrix
template<typename T, uint32_t N, uint32_t M>
Matrix<Complex<T>, M, N> conjugate_transpose(const Matrix<Complex<T>, N, M>& m) {
    Matrix<Complex<T>, M, N> result = mat::transpose(m);
    for (Complex<T>& i : result) {
        i.conjugate();
    }
    return result;
}

/// @brief Conjugate transpose a complex matrix
/// @tparam T The type of complex
/// @tparam N The row and column of the matrix
/// @param m The complex matrix
template<typename T, uint32_t N>
void self_conjugate_transpose(Matrix<Complex<T>, N, N>& m) {
    mat::self_transpose(m);
    for (Complex<T>& i : m) {
        i.conjugate();
    }
}

}