#pragma once

#include "Vector.hpp"

namespace mat {

//    ___     _                     _                          _              
//   | __|_ _| |_ ___ _ _ _ _  __ _| |  ___ _ __  ___ _ _ __ _| |_ ___ _ _ ___
//   | _|\ \ /  _/ -_) '_| ' \/ _` | | / _ \ '_ \/ -_) '_/ _` |  _/ _ \ '_(_-<
//   |___/_\_\\__\___|_| |_||_\__,_|_| \___/ .__/\___|_| \__,_|\__\___/_| /__/
//                                         |_|                                

/// @brief Stream operator, write the vector into a stream
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param stream The stream
/// @param v The vector
/// @return The stream with the modifications
template<typename T, uint32_t N>
std::ostream& operator<<(std::ostream& stream, const Vector<T,N>& v) {
    stream << "Vec[" << N << "](";
    for (uint32_t i(0) ; i < N ; ++i) {
        stream << v[i];
        i != N-1 ? stream << ", " : stream << ")" ;
    }
    return stream;
}

/// @brief Add a scalar to each element of the vector
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 The vector
/// @param a The scalar
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator+(Vector<T,N> v1, T a) {
    return v1 += a;
}

/// @brief Add a scalar to each element of the vector
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param a The scalar
/// @param v1 The vector
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator+(T a, Vector<T,N> v1) {
    return v1 += a;
}

/// @brief Substract a scalar to each element of the vector
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 The vector
/// @param a The scalar
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator-(Vector<T,N> v1, T a) {
    return v1 -= a;
}

/// @brief Substract element of the vector by a scalar
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param a The scalar
/// @param v1 The vector
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator-(T a, Vector<T,N> v1) {
    return v1 -= a;
}

/// @brief Multiply each component of a vector by a scalar
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 The vector
/// @param a The scalar
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator*(Vector<T,N> v1, T a) {
    return v1 *= a;
}

/// @brief Multiply each component of a vector by a scalar
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param a The scalar
/// @param v1 The vector
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator*(T a, Vector<T,N> v1) {
    return v1 *= a;
}

/// @brief Divide each component of a vector by a scalar
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 The vector
/// @param a The scalar
/// @return The new vector
template<typename T, uint32_t N>
Vector<T,N> operator/(Vector<T,N> v1, T a) {
    return v1 /= a;
}

/// @brief Addition of two vectors
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return The addition of the two vectors
template<typename T, uint32_t N>
Vector<T,N> operator+(Vector<T,N> v1, const Vector<T,N>& v2) {
    return v1 += v2;
}

/// @brief Substraction of two vectors
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return The substraction of the two vectors
template<typename T, uint32_t N>
Vector<T,N> operator-(Vector<T,N> v1, const Vector<T,N>& v2) {
    return v1 -= v2;
}

/// @brief Multiply each element of two vectors
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return The multiplication result
/// @warning It is not a dot product, use the function dot
template<typename T, uint32_t N>
Vector<T,N> operator*(Vector<T,N> v1, const Vector<T,N>& v2) {
    return v1 *= v2;
}

/// @brief Divide each element of two vectors
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return The division result
template<typename T, uint32_t N>
Vector<T,N> operator/(Vector<T,N> v1, const Vector<T,N>& v2) {
    return v1 /= v2;
}

/// @brief Each element is multiply by -1
/// @tparam T The type of vector
/// @tparam N The size of the vector
/// @param v1 The vector
/// @return Minus the vector (-v)
template<typename T, uint32_t N>
Vector<T,N> operator-(Vector<T,N> v1) {
    for (auto& i : v1) {
        i = -i;
    }
    return v1;
}

//    ___             _   _             
//   | __|  _ _ _  __| |_(_)___ _ _  ___
//   | _| || | ' \/ _|  _| / _ \ ' \(_-<
//   |_| \_,_|_||_\__|\__|_\___/_||_/__/
//                                      

/// @brief Sum all the component of a vector
/// @tparam T Type of the vector
/// @tparam N Size of the vector
/// @param v The vector
/// @return The sum of the component of the vector
template<typename T, uint32_t N>
T sum(const Vector<T,N>& v) {
    T result(0);
    for (auto i : v) {
        result += i;
    }
    return result;
}

/// @brief Merge two vectors into one vector
/// @tparam T Type of the vector
/// @tparam N Size of the first vector
/// @tparam M Size of the second vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return Merged vector
template<typename T, uint32_t N, uint32_t M>
Vector<T, N+M> merge(const Vector<T,N>& v1, const Vector<T,M>& v2) {
    Vector<T, N+M> result;
    uint32_t current(0);
    for (T& i : result) {
        current < N ? i = v1[current] : i = v2[current - N] ;
        ++current;
    }
    return result;
}

/// @brief Append a component at the back of a vector
/// @tparam T Type of the vector
/// @tparam N Size of the vector
/// @param v The vector
/// @param value The new component
/// @return Vector with the new element
template<typename T, uint32_t N>
Vector<T,N+1> append(const Vector<T,N>& v, T value) {
    Vector<T,N+1> result;
    std::copy(v.begin(), v.begin()+N, result.begin());
    result[N] = value;
    return result;
}

/// @brief Insert a component in a vector
/// @tparam T Type of the vector
/// @tparam N Size of the vector
/// @param v The vector
/// @param value The new component
/// @param index The index where the component will be inserted
/// @return Vector with the new element
template<typename T, uint32_t N>
Vector<T,N+1> insert(const Vector<T,N>& v, T value, uint32_t index) {
    Vector<T,N+1> result;
    std::copy(v.begin(), v.begin()+index, result.begin());
    std::copy(v.begin()+index, v.begin()+N, result.begin()+index+1);
    result[index] = value;
    return result;
}

/// @brief Remove a component from a vector
/// @tparam T Type of the vector
/// @tparam N Size of the vector
/// @param v The vector
/// @param index The index of the component that will be removed
/// @return Vector without the component
template<typename T, uint32_t N>
Vector<T,N-1> remove(const Vector<T,N>&v, uint32_t index) {
    Vector<T,N-1> result;
    std::copy(v.begin(), v.begin()+index, result.begin());
    std::copy(v.begin()+index+1, v.begin()+N, result.begin()+index);
    return result;
}

/// @brief Create a sub vector from a vector
/// @tparam T Type of the vector
/// @tparam N Size of the vector
/// @tparam I1 First element of the sub vector
/// @tparam I2 Last element of the sub vector
/// @param v The vector
/// @return The sub vector
template<typename T, uint32_t N, uint32_t I1, uint32_t I2>
Vector<T,I2-I1+1> sub_vector(const Vector<T,N>& v) {
    Vector<T,I2-I1+1> result;
    std::copy(v.begin()+I1, v.begin()+I2+1, result.begin());
    return result;
}

/// @brief Compute the dot product between two vectors
/// @tparam T Type of the vector
/// @tparam N Size of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return Result of the dot product
template<typename T, uint32_t N>
T dot(Vector<T,N> v1, const Vector<T,N>& v2) {
    return sum(v1*=v2);
}

/// @brief Compute the cross product between two vectors of dimension 2
/// @tparam T Type of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return Result of the cross product (a scalar)
template<typename T>
T cross(const Vector<T,2>& v1, const Vector<T,2>& v2) {
    return v1[0] * v2[1] - v1[1] * v2[0];
}

/// @brief Compute the cross product between two vectors of dimension 3
/// @tparam T Type of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return Result of the cross product (a vector 3)
template<typename T>
Vector<T,3> cross(const Vector<T,3>& v1, const Vector<T,3>& v2) {
    return Vector<T,3>{ v1[1] * v2[2] - v1[2] * v2[1],
                        v1[2] * v2[0] - v1[0] * v2[2],
                        v1[0] * v2[1] - v1[1] * v2[0]};
}

/// @brief Compute the angle between two vectors of dimension 2
/// @tparam T Type of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return Angle between the vectors
template<typename T>
T angle(const Vector<T,2>& v1, const Vector<T,2>& v2) {
    return atan2(cross(v1,v2), dot(v1,v2));
}

/// @brief Compute the angle between two vectors of dimension 3
/// @tparam T Type of the vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return Angle between the vectors
template<typename T>
T angle(const Vector<T,3>& v1, const Vector<T,3>& v2) {
    return atan2(cross(v1,v2).norm(), dot(v1,v2));
}

/// @brief Compute the polar representation of a vector 2
/// @tparam T Type of the vector
/// @param v The vector
/// @param radius A reference to the magnitude
/// @param theta A reference to the argument (angle) of the vector
template<typename T>
void polar(const Vector<T,2>& v, T& radius, T& theta) {
    radius = v.norm();
    theta = atan2(v[1], v[0]);
}

/// @brief Compute the cylindrical representation of a vector 3
/// @tparam T Type of the vector
/// @param v The vector
/// @param radius A reference to the radius of the cylinder
/// @param theta A reference to the angle
/// @param z A reference to the z coordinate
template<typename T>
void cylindrical(const Vector<T,3>& v, T& radius, T& theta, T& z) {
    radius = sqrt(v[0]*v[0] + v[1]*v[1]);
    theta = atan2(v[1], v[0]);
    z = v[2];
}

/// @brief Compute the spherical representation of a vector 3
/// @tparam T Type of the vector
/// @param v The vector
/// @param radius A reference to the radius of the sphere
/// @param theta A reference to the theta angle
/// @param phi A reference to the phi angle
template<typename T>
void spherical(const Vector<T,3>& v, T& radius, T& theta, T& phi) {
    radius = v.norm();
    theta = atan2(sqrt(v[0]*v[0] + v[1]*v[1]), v[2]);
    phi = atan2(v[1], v[0]);
}

/// @brief Compute the distance between two vectors
/// @tparam T Type of vector
/// @tparam N Size of vectors
/// @param v1 First vector
/// @param v2 Second vector
/// @return The distance between the vectors
template<typename T, uint32_t N>
T distance(const Vector<T,N>& v1, const Vector<T,N>& v2) {
    return (v1 - v2).norm();
}

/// @brief Compute the reflected vector
/// @tparam T Type of vector
/// @tparam N Site of vector
/// @param incident The incident ray
/// @param surface_normal The surface normal
/// @return The refleted vector
template<typename T, uint32_t N>
Vector<T,N> reflect(const Vector<T,N>& incident, Vector<T,N> surface_normal) {
    surface_normal.normalize();
    T two(2);
    return  incident - two*dot(incident,surface_normal)*surface_normal;
}

/// @brief Compute the refracted vector
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param incident The incident ray
/// @param surface_normal The surface normal
/// @param n1 The refraction index of the medium of the incident ray
/// @param n2 The refraction index of the medium of the surface
/// @return The refracted vector
template<typename T, uint32_t N>
Vector<T,N> refract(const Vector<T,N>& incident, Vector<T,N> surface_normal, T n1, T n2) {
    surface_normal.normalize();
    T one(1);
    T eta(n1/n2);
    T tmp_dot(dot(surface_normal,incident));
    return sqrt(one - eta*eta*(one - tmp_dot*tmp_dot)) * surface_normal +
        eta * (incident - tmp_dot * surface_normal);
}

/// @brief Get if both vector are facing in the same direction (dot(v1, v2) >? 0)
/// @tparam T Type of vector
/// @tparam N Size of vector
/// @param v1 First vector
/// @param v2 Second vector
/// @return True if dot(v1, v2) > 0, false otherwise
template<typename T, uint32_t N>
bool face_same_direction(const Vector<T,N>& v1, const Vector<T,N>& v2) {
    return dot(v1, v2) > T(0);
}

}