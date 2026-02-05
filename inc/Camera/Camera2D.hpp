#pragma once

#include "mat/Math.hpp"

namespace AMB {

class CameraOrthographic {
public:
    CameraOrthographic(mat::Vec2f position, mat::Vec2f dimension, float orientation = 0.0f, mat::Vec2f depth = mat::Vec2f{-1.0f, 1.0f});

    mat::Mat4f get_projection();

    mat::Mat4f get_view();

    mat::Mat4f get_vp();

    mat::Vec2f get_position() const;

    void set_position(mat::Vec2f position);

    void move(mat::Vec2f displacement);

    float get_orientation() const;

    void set_orientation(float angle);

    void rotate(float angle);

    void set_view_size(float width, float height);

    void set_depth(float near, float far);

private:
    void compute_matrices();

    mat::Mat4f m_projection;
    mat::Mat4f m_view;

    mat::Vec2f m_position;
    mat::Vec2f m_dimension;
    mat::Vec2f m_depth;
    float m_orientation;

    bool m_recompute;
};

}