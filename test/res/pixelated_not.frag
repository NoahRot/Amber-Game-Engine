#version 330 core
in vec2 v_uv;
out vec4 frag;

uniform sampler2D u_texture;
uniform vec2 u_resolution;
uniform float u_pixel_size;

void main() {
    frag = texture(u_texture, v_uv);

    //vec2 pixel = u_pixel_size / u_resolution; 
    //vec2 uv = floor(v_uv / pixel) * pixel; 
    //frag = texture(u_texture, uv);
}