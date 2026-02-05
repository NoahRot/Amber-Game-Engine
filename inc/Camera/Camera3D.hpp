#pragma once

#include "mat/Math.hpp"

namespace AMB {

class CameraPerspective {
public:
    CameraPerspective(mat::Vec3f position,
                      mat::Quatf orientation,
                      float aspect_ratio,
                      float fov,
                      float near_plane,
                      float far_plane);

    mat::Mat4f get_projection();

    mat::Mat4f get_view();

    mat::Mat4f get_vp();

    mat::Vec3f get_position() const;

    void set_position(const mat::Vec3f& pos);

    void move(const mat::Vec3f& displacement);

    mat::Quatf get_orientation() const;

    void get_orientation(float& pitch, float& yaw, float& roll);

    void set_orientation(const mat::Quatf& q);

    void set_orientation(const mat::Vec3f& look_at, const mat::Vec3f& up);

    void rotate(float pitch, float yaw, float roll);

private:
    void compute_matrices();

    mat::Mat4f m_projection;
    mat::Mat4f m_view;

    mat::Vec3f m_position;
    mat::Quatf m_orientation;

    float m_aspect_ratio;
    float m_fov;
    float m_near;
    float m_far;

    bool m_recompute;
};

}