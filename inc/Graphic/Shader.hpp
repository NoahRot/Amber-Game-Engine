#pragma once

#include <inttypes.h>
#include <unordered_map>
#include <string>
#include <glad/glad.h>

#include "mat/Math.hpp"

namespace AMB {

class Shader {
public:
    /// @brief Constructor
    /// @param index OpenGL index
    Shader(int32_t index);

    /// @brief Destructor
    ~Shader();

    /// @brief Use the shader for draw
    void use_shader() const;

    /// @brief Get the map of the uniform
    /// @return A constant reference to the map of uniform
    const std::unordered_map<std::string, int>& get_uniform_map() const;

    /// @brief Check the validity of a uniform variable name
    /// @param var_name Name of the variable
    /// @return True if the name is valid, False otherwise
    bool uniform_validity(const std::string& var_name) const;

    // Set the uniform variables

    void set_1i(const std::string& var_name, int var);
    void set_1f(const std::string& var_name, float var);
    void set_1d(const std::string& var_name, double var);

    void set_2i(const std::string& var_name, const mat::Vec2i& var);
    void set_2f(const std::string& var_name, const mat::Vec2f& var);
    void set_2d(const std::string& var_name, const mat::Vec2d& var);

    void set_3i(const std::string& var_name, const mat::Vec3i& var);
    void set_3f(const std::string& var_name, const mat::Vec3f& var);
    void set_3d(const std::string& var_name, const mat::Vec3d& var);

    void set_4i(const std::string& var_name, const mat::Vec4i& var);
    void set_4f(const std::string& var_name, const mat::Vec4f& var);
    void set_4d(const std::string& var_name, const mat::Vec4d& var);

    void set_mat3f(const std::string& var_name, const mat::Mat3f& var);
    void set_mat3d(const std::string& var_name, const mat::Mat3d& var);

    void set_mat4f(const std::string& var_name, const mat::Mat4f& var);
    void set_mat4d(const std::string& var_name, const mat::Mat4d& var);

private:
    /// @brief Map linking the name of the variables and the location
    std::unordered_map<std::string, int> m_uniform_map;

    /// @brief OpenGL index of the shader
    uint32_t m_index;
};

}