#pragma once

#include "Formula.hpp"
#include "Transform.hpp"

#include "BaseVector.hpp"
#include "BaseVectorFunction.hpp"

#include "Vector.hpp"
#include "VectorFunction.hpp"

#include "Matrix.hpp"
#include "MatrixFunction.hpp"

#include "Complex.hpp"
#include "ComplexFunction.hpp"

#include "Quaternion.hpp"
#include "QuaternionFunction.hpp"

// A macro used to know if the premade typedef have to be used 
// If 1: Use the typedef
// Otherwise, does not use them.
#ifndef MAT_TYPEDEF
#define MAT_TYPEDEF 1
#endif

namespace mat {

// Constant expression for the different component
constexpr uint32_t x = 0;
constexpr uint32_t y = 1;
constexpr uint32_t z = 2;
constexpr uint32_t w = 3;

constexpr double PI = 3.14159265358979323846264338327950288419716939937510582;
constexpr double PI_2 = 0.5*PI;
constexpr double PI_4 = 0.25*PI;

#if MAT_TYPEDEF == 1

typedef Vector<int,2> Vec2i;
typedef Vector<float,2> Vec2f;
typedef Vector<double,2> Vec2d;

typedef Vector<int,3> Vec3i;
typedef Vector<float,3> Vec3f;
typedef Vector<double,3> Vec3d;

typedef Vector<int,4> Vec4i;
typedef Vector<float,4> Vec4f;
typedef Vector<double,4> Vec4d;



typedef Matrix<int,2,2> Mat2i;
typedef Matrix<float,2,2> Mat2f;
typedef Matrix<double,2,2> Mat2d;

typedef Matrix<int,3,3> Mat3i;
typedef Matrix<float,3,3> Mat3f;
typedef Matrix<double,3,3> Mat3d;

typedef Matrix<int,4,4> Mat4i;
typedef Matrix<float,4,4> Mat4f;
typedef Matrix<double,4,4> Mat4d;



typedef Complex<int> Comi;
typedef Complex<float> Comf;
typedef Complex<double> Comd;



typedef Quaternion<int> Quati;
typedef Quaternion<float> Quatf;
typedef Quaternion<double> Quatd;

#endif

}