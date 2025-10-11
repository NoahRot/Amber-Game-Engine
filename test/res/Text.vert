#version 330 core
layout(location = 0) in vec3 a_position; // the position variable has attribute position 0
layout(location = 1) in vec2 a_texture_coord; // Textures coordinates

uniform mat4 u_mvp;
  
out vec2 texture_coord;

void main()
{
    vec4 position = vec4(a_position, 1.0);
    gl_Position = vec4(u_mvp*position); // see how we directly give a vec3 to vec4's constructor

    texture_coord = a_texture_coord;
}