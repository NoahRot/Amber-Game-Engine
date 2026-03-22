#include "Camera/Camera3D.hpp"

namespace AMB {

CameraPerspective::CameraPerspective(mat::Vec3f position,
                    mat::Quatf orientation,
                    float aspect_ratio,
                    float fov,
                    float near_plane,
                    float far_plane)
: m_position(position),
    m_orientation(orientation),
    m_aspect_ratio(aspect_ratio),
    m_fov(fov),
    m_near(near_plane),
    m_far(far_plane),
    m_recompute(true)
{
    compute_matrices();
}

mat::Mat4f CameraPerspective::get_projection() {
    compute_matrices();
    return m_projection;
}

mat::Mat4f CameraPerspective::get_view() {
    compute_matrices();
    return m_view;
}

mat::Mat4f CameraPerspective::get_vp() {
    compute_matrices();
    return mat::dot(m_projection, m_view);
}

mat::Vec3f CameraPerspective::get_position() const {
    return m_position;
}

void CameraPerspective::set_position(const mat::Vec3f& pos) {
    m_position = pos;
    m_recompute = true;
}

void CameraPerspective::move_global(const mat::Vec3f& displacement) {
    m_position += displacement;
    m_recompute = true;
}

void CameraPerspective::move_local(const mat::Vec3f& displacement) {
    m_position += mat::quat_rotate_vec<float>(m_orientation, displacement);
    m_recompute = true;
}

mat::Quatf CameraPerspective::get_orientation() const {
    return m_orientation;
}

void CameraPerspective::get_orientation(float& pitch, float& yaw, float& roll) {
    mat::quat_to_euler_angle<float>(m_orientation, roll, pitch, yaw);
}

void CameraPerspective::set_orientation(const mat::Quatf& q) {
    m_orientation = q;
    m_recompute = true;
}

//void CameraPerspective::set_orientation(const mat::Vec3f& look_at, mat::Vec3f up) {
//    mat::Vec3f forward = mat::normalize<float, 3>(look_at - m_position);
//    mat::Vec3f right = mat::normalize<float, 3>(mat::cross(forward, up));
//    mat::Vec3f up2 = mat::cross(right, forward);
//
//    mat::Mat3f R{
//        right[0],   up2[0],   -forward[0],
//        right[1],   up2[1],   -forward[1],
//        right[2],   up2[2],   -forward[2]
//    };
//
//    m_orientation = quat_from_rotation3(R);
//    m_recompute = true;
//}

void CameraPerspective::set_orientation(const mat::Vec3f& look_at,
                                        mat::Vec3f up)
{
    // Step 1: Compute forward direction (camera looks toward target)
    mat::Vec3f forward = look_at - m_position;

    // Prevent invalid orientation
    if (forward.norm2() == 0.0f)
        return;

    forward.normalize();

    // Step 2: Normalize the up vector
    up.normalize();

    // Step 3: Build orthonormal basis
    // Right-handed system: right = forward x up
    mat::Vec3f right = mat::cross<float>(forward, up);

    // Handle degenerate case (forward parallel to up)
    if (right.norm2() == 0.0f)
        return;

    right.normalize();

    // Recompute true up to ensure orthogonality
    mat::Vec3f up_corrected = mat::cross(right, forward);

    // Step 4: Convert basis to quaternion
    // Camera forward is -Z, so we negate forward
    const mat::Vec3f z = -forward;
    const mat::Vec3f x = right;
    const mat::Vec3f y = up_corrected;

    // Rotation matrix (column-major)
    float m00 = x[0], m01 = y[0], m02 = z[0];
    float m10 = x[1], m11 = y[1], m12 = z[1];
    float m20 = x[2], m21 = y[2], m22 = z[2];

    float trace = m00 + m11 + m22;

    mat::Quatf q;

    if (trace > 0.0f) {
        float s = std::sqrt(trace + 1.0f) * 2.0f;
        q[3] = 0.25f * s;
        q[0] = (m21 - m12) / s;
        q[1] = (m02 - m20) / s;
        q[2] = (m10 - m01) / s;
    }
    else if (m00 > m11 && m00 > m22) {
        float s = std::sqrt(1.0f + m00 - m11 - m22) * 2.0f;
        q[3] = (m21 - m12) / s;
        q[0] = 0.25f * s;
        q[1] = (m01 + m10) / s;
        q[2] = (m02 + m20) / s;
    }
    else if (m11 > m22) {
        float s = std::sqrt(1.0f + m11 - m00 - m22) * 2.0f;
        q[3] = (m02 - m20) / s;
        q[0] = (m01 + m10) / s;
        q[1] = 0.25f * s;
        q[2] = (m12 + m21) / s;
    }
    else {
        float s = std::sqrt(1.0f + m22 - m00 - m11) * 2.0f;
        q[3] = (m10 - m01) / s;
        q[0] = (m02 + m20) / s;
        q[1] = (m12 + m21) / s;
        q[2] = 0.25f * s;
    }

    m_orientation = q;
    m_recompute = true;
}

void CameraPerspective::rotate(float pitch, float yaw, float roll) {
    m_orientation *= mat::euler_angle_to_quat(roll, pitch, yaw);
    m_recompute = true;
}

void CameraPerspective::compute_matrices() {
    if (!m_recompute) return;

    m_projection = mat::graph::perspective<float>(
        m_aspect_ratio,
        m_fov,
        m_near,
        m_far
    );

    mat::Quatf inv_orientation = mat::conjugate(m_orientation);

    m_view = mat::dot(
        mat::graph::rotate3<float>(inv_orientation),
        mat::graph::translate3<float>(-m_position)
    );

    m_recompute = false;
}

}