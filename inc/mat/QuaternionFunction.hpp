#pragma once

#include "Quaternion.hpp"
#include "Vector.hpp"
#include <cmath>

namespace mat {

//    ___     _                     _                          _              
//   | __|_ _| |_ ___ _ _ _ _  __ _| |  ___ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | _|\ \ /  _/ -_) '_| ' \/ _` | | / _ \ '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//   |___/_\_\\__\___|_| |_||_\__,_|_| \___/ .__/\___|_| \__,_|\__\___/_| /__/
//                                         |_|                                

/// @brief Stream operator, write the quaternion into a stream
/// @tparam T Type of quaternion
/// @param stream The stream
/// @param q The quaternion
/// @return The stream with the modifications
template<typename T>
std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& q) {
    stream << "Quat(" << q.r() << " + " << q.i() << "i + " << q.j() << "j + " << q.k() << "k)";
    return stream;
}

/// @brief Add a real to a quaternion
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @param a The real
/// @return The new quaternion
template<typename T>
Quaternion<T> operator+(Quaternion<T> q, T a) {
    return q += a;
}

/// @brief Add a real to a quaternion
/// @tparam T Type of quaternion
/// @param a The real
/// @param q The quaternion
/// @return The new quaternion
template<typename T>
Quaternion<T> operator+(T a, Quaternion<T> q) {
    return q += a;
}

/// @brief Substract a real to a quaternion
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @param a The real
/// @return The new quaternion
template<typename T>
Quaternion<T> operator-(Quaternion<T> q, T a) {
    return q -= a;
}

/// @brief Substract a quaternion to a real
/// @tparam T Type of quaternion
/// @param a The real
/// @param q The quaternion
/// @return The new quaternion
template<typename T>
Quaternion<T> operator-(T a, Quaternion<T> q) {
    return -q += a;
}

/// @brief Multiply a quaternion by a real
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @param a The real
/// @return The new quaternion
template<typename T>
Quaternion<T> operator*(Quaternion<T> q, T a) {
    return q *= a;
}

/// @brief Multiply a quaternion by a real
/// @tparam T Type of quaternion
/// @param a The real
/// @param q The quaternion
/// @return The new quaternion
template<typename T>
Quaternion<T> operator*(T a, Quaternion<T> q) {
    return q *= a;
}

/// @brief Divide a quaternion by a real
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @param a The real
/// @return The new quaternion
template<typename T>
Quaternion<T> operator/(Quaternion<T> q, T a) {
    return q /= a;
}

/// @brief Addition of two quaternions
/// @tparam T Type of quaternion
/// @param q1 First quaternion
/// @param q2 Second quaternion
/// @return The addition of the quaternion
template<typename T>
Quaternion<T> operator+(Quaternion<T> q1, const Quaternion<T>& q2) {
    return q1 += q2;
}

/// @brief Substraction of two quaternions
/// @tparam T Type of quaternion
/// @param q1 First quaternion
/// @param q2 Second quaternion
/// @return The substraction of the quaternion
template<typename T>
Quaternion<T> operator-(Quaternion<T> q1, const Quaternion<T>& q2) {
    return q1 -= q2;
}

/// @brief Multiplication of two quaternions
/// @tparam T Type of quaternion
/// @param q1 First quaternion
/// @param q2 Second quaternion
/// @return The multiplication of the quaternion
template<typename T>
Quaternion<T> operator*(Quaternion<T> q1, const Quaternion<T>& q2) {
    return q1 *= q2;
}

/// @brief Multiply the quaternion by -1
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return Minus the quaternion (-q)
template<typename T>
Quaternion<T> operator-(const Quaternion<T>& q) {
    return Quaternion<T>(-q.r(), -q.i(), -q.j(), -q.k());
}

//    ___             _   _             
//   | __|  _ _ _  __| |_(_)___ _ _  ___
//   | _| || | ' \/ _|  _| / _ \ ' \(_-<
//   |_| \_,_|_||_\__|\__|_\___/_||_/__/
//                                      

/// @brief From a quaternion to a rotation matrix (3x3)
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return The rotation matrix (3x3)
template<typename T>
Matrix<T,3,3> quat_to_rotation3(const Quaternion<T>& q) {
    T two(2);
    T one(1);
    return Matrix<T,3,3>{
        two*(q[0]*q[0] + q[1]*q[1]) - one,  two*(q[1]*q[2] + q[0]*q[3]),        two*(q[1]*q[3] - q[0]*q[2]),
        two*(q[1]*q[2] - q[0]*q[3]),        two*(q[0]*q[0] + q[2]*q[2]) - one,  two*(q[2]*q[3] + q[0]*q[1]),
        two*(q[1]*q[3] + q[0]*q[2]),        two*(q[2]*q[3] - q[0]*q[1]),        two*(q[0]*q[0] + q[3]*q[3]) - one
    };
}

/// @brief From a quaternion to a rotation matrix (4x4)
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return The rotation matrix (4x4) (last line and column fill with 0 except the diagonal term which is 1)
template<typename T>
Matrix<T,4,4> quat_to_rotation4(const Quaternion<T>& q) {
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

/// @brief Get the vector of the rotation
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return The vector of rotation
template<typename T>
Vector<T,3> quat_to_vec_of_rotation(const Quaternion<T>& q) {
    return q.imag();
}

/// @brief Get the angle of rotation
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return The angle of rotation
template<typename T>
T quat_to_angle_of_rotation(const Quaternion<T>& q) {
    return 2*acos(q[0]);
}

/// @brief Compute a quaternion from a vector of rotation and  an angle
/// @tparam T Type of quaternion
/// @param angle The angle
/// @param vec The vector of rotation
/// @return The quaternion that represent the rotation
template<typename T>
Quaternion<T> quat_from_angle_vec_of_rotation(T angle, Vector<T,3> vec) {
    vec.normalize();
    T C = cos(angle/2);
    T S = sin(angle/2);
    return Quaternion<T>{C, S*vec[0], S*vec[1], S*vec[2]};
}

/// @brief Compute the quaternion from the Euler angles
/// @tparam T Type of quaternion
/// @param roll Roll angle (around x)
/// @param pitch Pitch angle (around y)
/// @param yaw Yaw angle (around z)
/// @return The quaternion that represent the rotation
template<typename T>
Quaternion<T> euler_angle_to_quat(T roll, T pitch, T yaw) {
    T half(0.5);
    T cr = cos(roll * half);
    T sr = sin(roll * half);
    T cp = cos(pitch * half);
    T sp = sin(pitch * half);
    T cy = cos(yaw * half);
    T sy = sin(yaw * half);

    return Quaternion<T>{
        cr*cp*cy + sr*sp*sy,
        sr*cp*cy - cr*sp*sy,
        cr*sp*cy + sr*cp*sy,
        cr*cp*sy - sr*sp*cy
    };
}

/// @brief Get the Euler angles from a quaternion
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @param roll Reference to the roll angle (around x)
/// @param pitch Reference to the pitch angle (around y)
/// @param yaw Reference to the yaw angle (around z)
template<typename T>
void quat_to_euler_angle(const Quaternion<T>& q, T& roll, T& pitch, T& yaw) {
    T two(2);
    T one(1);
    T half_pi(0.5 * 3.14159265358979323846264338327950288419716939937510582);
    roll = atan2(two*(q[0]*q[1] + q[2]*q[3]), one - two*(q[1]*q[1] + q[2]*q[2]));
    pitch = -half_pi + two*atan2(sqrt(one + two*(q[0]*q[2] - q[1]*q[3])), sqrt(one - two*(q[0]*q[2] - q[1]*q[3])));
    yaw = atan2(two*(q[0]*q[3] + q[1]*q[2]), one - two*(q[2]*q[2] + q[3]*q[3]));
}

/// @brief Rotate a vector using a quaternion
/// @tparam T Type of quaternion and vector
/// @param q The quaternion
/// @param v The vector
/// @return The rotated vector
template<typename T>
Vector<T,3> quat_rotate_vec(const Quaternion<T>& q, const Vector<T,3>& v) {
    Quaternion<T> vq{0, v[0], v[1], v[2]};
    return (q * vq * conjugate(q)).imag();
}

/// @brief Conjugate the quaternion
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return The conjugated quaternion
template<typename T>
Quaternion<T> conjugate(Quaternion<T> q) {
    q.conjugate();
    return q;
}

/// @brief Inverse the quaternion
/// @tparam T Type of quaternion
/// @param q The quaternion
/// @return The inversed quaternion
template<typename T>
Quaternion<T> inverse(const Quaternion<T>& q) {
    return conjugate(q) * 1.0/(q.norm2());
}

}