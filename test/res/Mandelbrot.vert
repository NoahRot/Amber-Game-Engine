#version 330 core

layout (location = 0) in vec2 a_position;      // Position (x, y)
layout (location = 1) in vec2 a_texture_coord; // Texture UVs

out vec2 texture_coord; // Pass to fragment shader

uniform mat4 u_mvp;

void main() {
    texture_coord = a_texture_coord;                    // Pass UV coordinates
    gl_Position = u_mvp*vec4(a_position, 0.0, 1.0);   // Transform position;
}