#version 330 core
in vec2 v_uv;
out vec4 frag;

uniform sampler2D u_texture;
uniform vec2 u_texel_size;   // 1.0 / texture resolution
uniform bool u_horizontal;   // horizontal or vertical pass

void main() {
    float weight[5] = float[](0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f);
    vec3 result = texture(u_texture, v_uv).rgb * weight[0];

    for (int horiz = 0 ; horiz < 2 ; ++ horiz){
        for(int i = 1; i < 5; ++i) {
            vec2 offset = u_texel_size * float(i);
            if(horiz%2 == 0) {
                result += texture(u_texture, v_uv + vec2(offset.x, 0.0)).rgb * weight[i];
                result += texture(u_texture, v_uv - vec2(offset.x, 0.0)).rgb * weight[i];
            } else {
                result += texture(u_texture, v_uv + vec2(0.0, offset.y)).rgb * weight[i];
                result += texture(u_texture, v_uv - vec2(0.0, offset.y)).rgb * weight[i];
            }
        }
    }

    frag = vec4(result, 1.0);
}