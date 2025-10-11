// triangle.frag
#version 330 core
in vec2 texture_coord;

uniform sampler2D u_texture;

out vec4 frag_color;
in vec4 vertex_color;

void main()
{
    float alpha = texture(u_texture, texture_coord).r; // Use red channel as alpha
    frag_color = vec4(vertex_color.r, vertex_color.g, vertex_color.b, vertex_color.a * alpha);
}