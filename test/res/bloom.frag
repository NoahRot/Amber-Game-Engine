#version 330 core
in vec2 v_uv;
out vec4 frag;

uniform sampler2D u_scene;
uniform sampler2D u_effet;
uniform float u_bloom_intensity = 1.0;

void main() {
    vec3 scene = texture(u_scene, v_uv).rgb;
    vec3 bloom = texture(u_effet, v_uv).rgb;

    frag = vec4(scene + bloom, 1.0);
}
