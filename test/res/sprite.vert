#version 330 core

layout (location = 0) in vec3 a_position;      // Position (x, y)
layout (location = 1) in vec2 a_texture_coord; // Texture UVs

uniform mat4 u_mvp; // Orthographic projection matrix

out vec2 texture_coord; // Pass to fragment shader

void main() {
    texture_coord = a_texture_coord;                // Pass UV coordinates
    gl_Position = u_mvp * vec4(a_position, 1.0);    // Transform position
}