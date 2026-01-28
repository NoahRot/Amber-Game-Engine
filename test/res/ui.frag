// triangle.frag
#version 330 core

uniform sampler2D u_texture;
uniform sampler2D u_font;

out vec4 frag_color;

in vec2 texture_coord;
in vec4 vertex_color;
flat in float render_mode;

void main()
{
    frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    if (int(render_mode) == 0) {        // Flat color mode
        frag_color = vertex_color;
    }else if(int(render_mode) == 1){    // Texture mode
        frag_color = texture(u_texture, texture_coord);
    }else{                              // Text mode
        float alpha = texture(u_font, texture_coord).r;
        frag_color = vec4(vertex_color.r, vertex_color.g, vertex_color.b, vertex_color.a * alpha);
        //frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    }
}