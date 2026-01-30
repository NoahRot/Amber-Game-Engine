#version 330 core
in vec2 v_uv;
out vec4 frag;

uniform sampler2D u_texture;
uniform float u_threshold = 1.0; // brightness threshold

void main() {
    vec3 color = texture(u_texture, v_uv).rgb;
    float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > u_threshold) {
        frag = vec4(color, 1.0);
    } else {
        frag = vec4(0.0);
    }
}
