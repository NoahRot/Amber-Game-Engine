#include "Graphic/Shader.hpp"

namespace AMB {

Shader::Shader(int32_t index)
: m_index(index)
{
    // Find all uniform variables
    int uniform_count = 0;

    // Query the number of active uniforms in the shader program
    glGetProgramiv(m_index, GL_ACTIVE_UNIFORMS, &uniform_count);

    char uniform_name[256];
    for (int i = 0; i < uniform_count; i++) {
        GLint size;
        GLenum type;

        // Get uniform info
        glGetActiveUniform(m_index, i, sizeof(uniform_name), nullptr, &size, &type, uniform_name);

        // Get uniform location
        int location = glGetUniformLocation(m_index, uniform_name);
        if (location != -1) {  // If uniform exists in the program
            m_uniform_map[uniform_name] = location;
        }
    }
}

Shader::~Shader() {
    glDeleteProgram(m_index);
}

void Shader::use_shader() const {
    glUseProgram(m_index);
}

const std::unordered_map<std::string, int>& Shader::get_uniform_map() const {
    return m_uniform_map;
}

bool Shader::uniform_validity(const std::string& var_name) const {
    return m_uniform_map.find(var_name) != m_uniform_map.end();
}

void Shader::set_1i(const std::string& var_name, int var) {
    glUniform1i(m_uniform_map[var_name], var);
}

void Shader::set_1f(const std::string& var_name, float var) {
    glUniform1f(m_uniform_map[var_name], var);
}

void Shader::set_1d(const std::string& var_name, double var) {
    glUniform1d(m_uniform_map[var_name], var);
}

void Shader::set_2i(const std::string& var_name, const mat::Vec2i& var) {
    glUniform2i(m_uniform_map[var_name], var[0], var[1]);
}

void Shader::set_2f(const std::string& var_name, const mat::Vec2f& var) {
    glUniform2f(m_uniform_map[var_name], var[0], var[1]);
}

void Shader::set_2d(const std::string& var_name, const mat::Vec2d& var) {
    glUniform2d(m_uniform_map[var_name], var[0], var[1]);
}

void Shader::set_3i(const std::string& var_name, const mat::Vec3i& var) {
    glUniform3i(m_uniform_map[var_name], var[0], var[1], var[2]);
}

void Shader::set_3f(const std::string& var_name, const mat::Vec3f& var) {
    glUniform3f(m_uniform_map[var_name], var[0], var[1], var[2]);
}

void Shader::set_3d(const std::string& var_name, const mat::Vec3d& var) {
    glUniform3d(m_uniform_map[var_name], var[0], var[1], var[2]);
}

void Shader::set_4i(const std::string& var_name, const mat::Vec4i& var) {
    glUniform4i(m_uniform_map[var_name], var[0], var[1], var[2], var[3]);
}

void Shader::set_4f(const std::string& var_name, const mat::Vec4f& var) {
    glUniform4f(m_uniform_map[var_name], var[0], var[1], var[2], var[3]);
}

void Shader::set_4d(const std::string& var_name, const mat::Vec4d& var) {
    glUniform4d(m_uniform_map[var_name], var[0], var[1], var[2], var[3]);
}

void Shader::set_mat3f(const std::string& var_name, const mat::Mat3f& var) {
    glUniformMatrix3fv(m_uniform_map[var_name], 1, false, &var(0,0));
}

void Shader::set_mat3d(const std::string& var_name, const mat::Mat3d& var) {
    glUniformMatrix3dv(m_uniform_map[var_name], 1, false, &var(0,0));
}

void Shader::set_mat4f(const std::string& var_name, const mat::Mat4f& var) {
    glUniformMatrix4fv(m_uniform_map[var_name], 1, false, &var(0,0));
}

void Shader::set_mat4d(const std::string& var_name, const mat::Mat4d& var) {
    glUniformMatrix4dv(m_uniform_map[var_name], 1, false, &var(0,0));
}

}