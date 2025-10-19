#version 330 core

in vec2 texture_coord; // Pass to fragment shader

out vec4 frag_color;

uniform sampler2D u_texture; // Texture atlas

void main() {
    frag_color = texture(u_texture, texture_coord);
}