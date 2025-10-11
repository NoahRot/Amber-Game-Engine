// triangle.frag
#version 330 core
in vec2 texture_coord;

uniform sampler2D u_texture;
uniform vec4 u_color;

out vec4 frag_color;

void main()
{
    float alpha = texture(u_texture, texture_coord).r; // Use red channel as alpha
    frag_color = vec4(u_color.r, u_color.g, u_color.b, u_color.a * alpha);
}