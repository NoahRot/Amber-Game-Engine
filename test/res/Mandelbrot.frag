#version 330 core

in vec2 texture_coord;

out vec4 frag_color;

uniform usampler2D u_texture;
uniform float u_max_iter;
uniform bool u_mouse_quad;
uniform ivec2 u_mouse_pos0;
uniform ivec2 u_mouse_pos1;
uniform float u_win_ratio;
uniform int u_color_selection;

vec3 getColorWhite(float t) {
    return vec3(t, t, t);
}

vec3 getColorFire(float t) {
    t = clamp(t, 0.0, 1.0);
    return vec3(
        smoothstep(0.0, 0.5, t),
        smoothstep(0.2, 0.8, t) * 0.6,
        smoothstep(0.5, 1.0, t) * 0.3
    );
}

vec3 getColorOcean(float t) {
    t = clamp(t, 0.0, 1.0);
    float r = 0.2 + 0.8 * t;
    float g = 0.5 + 0.5 * sin(3.0 * t);
    float b = 1.0 - 0.8 * pow(t, 2.0);
    return vec3(r, g, b);
}

vec3 getColorVidris(float t)
{
    // Clamp to [0,1]
    t = clamp(t, 0.0, 1.0);

    // Viridis polynomial approximation
    const vec3 c0 = vec3(0.267004, 0.004874, 0.329415);
    const vec3 c1 = vec3(0.255073, 0.265254, 0.529983);
    const vec3 c2 = vec3(0.206756, 0.521223, 0.656921);
    const vec3 c3 = vec3(0.163625, 0.733059, 0.625518);
    const vec3 c4 = vec3(0.993248, 0.906157, 0.143936);

    // Smooth interpolation between control points
    if (t < 0.25)
        return mix(c0, c1, t / 0.25);
    else if (t < 0.5)
        return mix(c1, c2, (t - 0.25) / 0.25);
    else if (t < 0.75)
        return mix(c2, c3, (t - 0.5) / 0.25);
    else
        return mix(c3, c4, (t - 0.75) / 0.25);
}

vec3 getColorInferno(float t) {
    return mix(
        mix(vec3(0.0, 0.0, 0.0), vec3(0.8, 0.1, 0.0), smoothstep(0.0, 0.4, t)),
        vec3(1.0, 1.0, 0.8),
        smoothstep(0.5, 1.0, t)
    );
}

vec3 getColorMagma(float t) {
    t = clamp(t, 0.0, 1.0);
    return mix(
        mix(vec3(0.0, 0.0, 0.2), vec3(0.8, 0.0, 0.4), smoothstep(0.0, 0.4, t)),
        vec3(1.0, 0.9, 0.7),
        smoothstep(0.5, 1.0, t)
    );
}

vec3 getColorPlasma(float t) {
    t = clamp(t, 0.0, 1.0);
    return mix(
        mix(vec3(0.05, 0.0, 0.4), vec3(0.8, 0.0, 0.8), smoothstep(0.0, 0.5, t)),
        vec3(1.0, 1.0, 0.0),
        smoothstep(0.5, 1.0, t)
    );
}

vec3 getColorCividis(float t) {
    t = clamp(t, 0.0, 1.0);
    return mix(vec3(0.0, 0.32, 0.55), vec3(1.0, 0.9, 0.4), t);
}

vec3 getCustomPalette(float t) {
    // Clamp t to [0, 1]
    t = clamp(t, 0.0, 1.0);

    // Define the five colors as RGB in 0–1 range
    const vec3 c0 = vec3(0.000, 0.118, 0.235); // #003f5c
    const vec3 c1 = vec3(0.345, 0.314, 0.553); // #58508d
    const vec3 c2 = vec3(0.737, 0.314, 0.565); // #bc5090
    const vec3 c3 = vec3(1.000, 0.388, 0.380); // #ff6361
    const vec3 c4 = vec3(1.000, 0.651, 0.000); // #ffa600

    // Divide t into 4 segments between the 5 colors
    if (t < 0.25)
        return mix(c0, c1, t / 0.25);
    else if (t < 0.5)
        return mix(c1, c2, (t - 0.25) / 0.25);
    else if (t < 0.75)
        return mix(c2, c3, (t - 0.5) / 0.25);
    else
        return mix(c3, c4, (t - 0.75) / 0.25);
}

vec3 getColorGradient(float t, vec3 colorA, vec3 colorB) {
    t = clamp(t, 0.0, 1.0);
    return mix(colorA, colorB, t);
}

vec3 getColorMod(int iter, int modulo) {
    int i = iter%modulo;
    float t = float(i)/float(modulo);

    //return getCustomPalette(t);
    return vec3(getColorGradient(t, vec3(0.0,0.1,0.5), vec3(1.0,0.6,0.0)));
}

vec3 getColorModRGB(int iter, int modulo) {
    // compute fractional position within current band
    int band = (iter / modulo) % 3;  // which band (0=R, 1=G, 2=B)
    float t = float(iter % modulo) / float(modulo);

    vec3 color;

    if (band == 0)
        color = vec3(t, 0.0, 0.0); // Red ramp
    else if (band == 1)
        color = vec3(0.0, t, 0.0); // Green ramp
    else
        color = vec3(0.0, 0.0, t); // Blue ramp

    return color;
}

void main() {
    uint iter = texture(u_texture, texture_coord).r;
    float t = clamp(float(iter) / u_max_iter, 0.0, 1.0);

    if (iter >= uint(u_max_iter)) {
        frag_color = vec4(0.0, 0.0, 0.0, 1.0); // inside set = black
    } else {
        //frag_color = vec4(getCividis(t), 1.0);
        //frag_color = vec4(getColorModRGB(int(iter), 20), 1.0);

        if (u_color_selection == 1) {
            frag_color = vec4(getColorVidris(t), 1.0);
        }else if (u_color_selection == 2) {
            frag_color = vec4(getColorFire(t), 1.0);
        }else if (u_color_selection == 3) {
            frag_color = vec4(getColorOcean(t), 1.0);
        }else if (u_color_selection == 4) {
            frag_color = vec4(getColorInferno(t), 1.0);
        }else if (u_color_selection == 5) {
            frag_color = vec4(getColorPlasma(t), 1.0);
        }else if (u_color_selection == 6) {
            frag_color = vec4(getColorMagma(t), 1.0);
        }else if (u_color_selection == 7) {
            frag_color = vec4(getColorCividis(t), 1.0);
        }else if (u_color_selection == 8) {
            frag_color = vec4(getCustomPalette(t), 1.0);
        }else if (u_color_selection == 9) {
            frag_color = vec4(getColorMod(int(iter), 10), 1.0);
        }else if (u_color_selection == 10) {
            frag_color = vec4(getColorModRGB(int(iter), 10), 1.0);
        }else {
            frag_color = vec4(getColorWhite(t), 1.0);
        }
    }

    // Mouse quad
    // Get the pixel being processed
    ivec2 frag_pixel = ivec2(gl_FragCoord.xy);

    // Draw a rectangle
    int lw = 1;
    float x_length = u_mouse_pos0.x - u_mouse_pos1.x;
    float y_length = x_length/u_win_ratio;

    ivec2 mouse_pos0 = ivec2(u_mouse_pos0.x - x_length, u_mouse_pos0.y - y_length);
    ivec2 mouse_pos1 = ivec2(u_mouse_pos0.x + x_length, u_mouse_pos0.y + y_length);
    if (u_mouse_quad &&
        ((abs(frag_pixel.x - mouse_pos0.x) <= lw) ||
        (abs(frag_pixel.x - mouse_pos1.x) <= lw) ||
        (abs(frag_pixel.y - mouse_pos0.y) <= lw) ||
        (abs(frag_pixel.y - mouse_pos1.y) <= lw)))
    {
        frag_color = vec4(1.0-frag_color.rgb, frag_color.a); // highlight color
    }
}