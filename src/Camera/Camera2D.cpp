#include "Camera/Camera2D.hpp"

namespace AMB {

CameraOrthographic::CameraOrthographic(mat::Vec2f position, mat::Vec2f dimension, float orientation, mat::Vec2f depth)
: m_position(position), m_dimension(dimension), m_depth(depth), m_orientation(orientation), m_recompute(true)
{
    compute_matrices();
}

mat::Mat4f CameraOrthographic::get_projection() {
    compute_matrices();
    return m_projection;
}

mat::Mat4f CameraOrthographic::get_view() {
    compute_matrices();
    return m_view;
}

mat::Mat4f CameraOrthographic::get_vp() {
    compute_matrices();
    return mat::dot(m_projection, m_view);
}

mat::Vec2f CameraOrthographic::get_position() const {
    return m_position;
}

void CameraOrthographic::set_position(mat::Vec2f position) {
    m_position = position;
    m_recompute = true;
}

void CameraOrthographic::move(mat::Vec2f displacement) {
    m_position += displacement;
    m_recompute = true;
}

float CameraOrthographic::get_orientation() const {
    return m_orientation;
}

void CameraOrthographic::set_orientation(float angle) {
    m_orientation = angle;
    m_recompute = true;
}

void CameraOrthographic::rotate(float angle) {
    m_orientation += angle;
    m_recompute = true;
}

void CameraOrthographic::set_view_size(float width, float height) {
    m_dimension[0] = width;
    m_dimension[1] = height;
    m_recompute = true;
}

void CameraOrthographic::set_depth(float near, float far) {
    m_depth[0] = near;
    m_depth[1] = far;
    m_recompute = true;
}

void CameraOrthographic::compute_matrices() {
    if (!m_recompute) { return; }
    m_projection = mat::orthographic3<float>(-0.5f * m_dimension[0], 0.5f * m_dimension[0], -0.5f * m_dimension[1], 0.5f * m_dimension[1], m_depth[0], m_depth[1]);
    m_view = mat::dot(mat::rotateZ<float>(-m_orientation), mat::translate3<float>(mat::Vec3f{-m_position[0], -m_position[1], 0.0f}));
    m_recompute = false;
}

}