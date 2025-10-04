#pragma once

#include <cmath>

#include "Matrix.hpp"
#include "Complex.hpp"
#include "Quaternion.hpp"

namespace mat {

// 2D Transformations

template<typename T>
Matrix<T, 3, 3> translate2(const Vector<T,2>& v) {
    T zero(0);
    T one(1);
    return Matrix<T,3,3>{
        one,    zero,   v[0],
        zero,   one,    v[1],
        zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 3, 3> rotate2(T angle) {
    T c = cos(angle);
    T s = sin(angle);
    T zero(0);
    T one(1);
    return  Matrix<T, 3, 3>{
        c,      s,      zero,
        -s,     c,      zero,
        zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 3, 3> rotate2(const Complex<T>& c) {
    T co = c.real() / c.modulus();
    T si = c.imag() / c.modulus();
    T zero(0);
    T one(1);
    return Matrix<T,3,3>{
        co,     si,     zero,
        -si,    co,     zero,
        zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 3, 3> scale2(T sx, T sy) {
    T zero(0);
    T one(1);
    return Matrix<T,3,3>{
        sx,     zero,   zero,
        zero,   sy,     zero,
        zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 3, 3> scale2(T s) {
    T zero(0);
    T one(1);
    return Matrix<T,3,3>{
        s,      zero,   zero,
        zero,   s,      zero,
        zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 3, 3> orthographic2(T left, T right, T bottom, T top) {
    T zero(0);
    T one(1);
    T two(2);
    return Matrix<T,3,3>{
        two/(right-left),           zero,                       zero,
        zero,                       two/(top-bottom),           zero,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), one

    };
}

// 3D Transformations

template<typename T>
Matrix<T, 4, 4> translate3(const Vector<T,3>& vect) {
    T zero(0);
    T one(1);
    return Matrix<T,4,4>{
        one,    zero,   zero,   zero,
        zero,   one,    zero,   zero,
        zero,   zero,   one,    zero,
        vect[0],vect[1],vect[2],one
    };
}

template<typename T>
Matrix<T, 4, 4> rotateX(T angle) {
    T zero(0);
    T one(1);
    T c = cos(angle);
    T s = sin(angle);
    return Matrix<T,4,4>{
        one,    zero,   zero,   zero,
        zero,   c,      s,      zero,
        zero,   -s,     c,      zero,
        zero,   zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 4, 4> rotateY(T angle) {
    T zero(0);
    T one(1);
    T c = cos(angle);
    T s = sin(angle);
    return Matrix<T,4,4>{
        c,      zero,   -s,     zero,
        zero,   one,     zero,  zero,
        s,      zero,    c,     zero,
        zero,   zero,   zero,   one
    };  
}

template<typename T>
Matrix<T, 4, 4> rotateZ(T angle) {
    T zero(0);
    T one(1);
    T c = cos(angle);
    T s = sin(angle);
    return Matrix<T,4,4>{
        c,      s,      zero,   zero,
        -s,     c,      zero,   zero,
        zero,   zero,   one,    zero,
        zero,   zero,   zero,   one
    }; 
}

template<typename T>
Matrix<T, 4, 4> rotate3(const Quaternion<T>& q) {
    T two(2);
    T one(1);
    T zero(0);
    return Matrix<T,4,4>{
        two*(q[0]*q[0] + q[1]*q[1]) - one,  two*(q[1]*q[2] + q[0]*q[3]),        two*(q[1]*q[3] - q[0]*q[2]),        zero,
        two*(q[1]*q[2] - q[0]*q[3]),        two*(q[0]*q[0] + q[2]*q[2]) - one,  two*(q[2]*q[3] + q[0]*q[1]),        zero,
        two*(q[1]*q[3] + q[0]*q[2]),        two*(q[2]*q[3] - q[0]*q[1]),        two*(q[0]*q[0] + q[3]*q[3]) - one,  zero,
        zero,                               zero,                               zero,                               one
    };
}

template<typename T>
Matrix<T, 4, 4> scale3(T sx, T sy, T sz) {
    T zero(0);
    T one(1);
    return Matrix<T,4,4>{
        sx,     zero,   zero,   zero,
        zero,   sy,     zero,   zero,
        zero,   zero,   sz,     zero,
        zero,   zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 4, 4> scale3(T s) {
    T zero(0);
    T one(1);
    return Matrix<T,4,4>{
        s,      zero,   zero,   zero,
        zero,   s,      zero,   zero,
        zero,   zero,   s,      zero,
        zero,   zero,   zero,   one
    };
}

template<typename T>
Matrix<T, 4, 4> orthographic3(T left, T right, T bottom, T top, T near, T far) {
    T zero(0);
    T one(1);
    T two(2);
    return Matrix<T,4,4>{
        two/(right-left),           zero,                       zero,                   zero,
        zero,                       two/(top-bottom),           zero,                   zero,
        zero,                       zero,                       -two/(far-near),        zero,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near), one
    };
}

template<typename T>
Matrix<T, 4, 4> perspective(T aspectRatio, T fov, T n, T f) {
    T t = tanf(0.5f*fov)*n;
    T b = -t;
    T r = t*aspectRatio;
    T l = -r;
    T zero(0);
    T one(1);
    return Matrix<T,4,4>{
        2*n/(r-l),      zero,           zero,           zero,
        zero,           2*n/(t-b),      zero,           zero,
        (r+l)/(r-l),    (t+b)/(t-b),    -(f+n)/(f-n),   -one,
        zero,           zero,           -2*f*n/(f-n),   zero
    };
}
    
}