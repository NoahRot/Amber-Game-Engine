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

void CameraPerspective::move(const mat::Vec3f& displacement) {
    m_position += displacement;
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

void CameraPerspective::set_orientation(const mat::Vec3f& look_at, const mat::Vec3f& up) {
    mat::Vec3f forward = mat::normalize<float, 3>(look_at - m_position);
    mat::Vec3f right = mat::normalize<float, 3>(mat::cross(forward, up));
    mat::Vec3f up2 = mat::cross(right, forward);

    mat::Mat3f R{
        right[0],   up2[0],   -forward[0],
        right[1],   up2[1],   -forward[1],
        right[2],   up2[2],   -forward[2]
    };

    m_orientation = quat_from_rotation3(R);
    m_recompute = true;
}

void CameraPerspective::rotate(float pitch, float yaw, float roll) {
    m_orientation *= mat::euler_angle_to_quat(roll, pitch, yaw);
    m_recompute = true;
}

void CameraPerspective::compute_matrices() {
    if (!m_recompute) return;

    m_projection = mat::perspective<float>(
        m_fov,
        m_aspect_ratio,
        m_near,
        m_far
    );

    mat::Quatf inv_orientation = mat::conjugate(m_orientation);

    m_view = mat::dot(
        mat::rotate3<float>(inv_orientation),
        mat::translate3<float>(-m_position)
    );

    m_recompute = false;
}

}