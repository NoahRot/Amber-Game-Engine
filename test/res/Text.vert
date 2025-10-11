#version 330 core
layout(location = 0) in vec3 a_position; // the position variable has attribute position 0
layout(location = 1) in vec4 a_color; // The color variable has attribute position 1
layout(location = 2) in vec2 a_texture_coord; // The texture coordinate variable has attribute position 2

uniform mat4 u_mvp;
  
out vec2 texture_coord;
out vec4 vertex_color;

void main()
{
    vec4 position = vec4(a_position, 1.0);
    gl_Position = vec4(u_mvp*position); // see how we directly give a vec3 to vec4's constructor

    texture_coord = a_texture_coord;
    vertex_color = a_color;
}