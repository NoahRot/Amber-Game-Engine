#version 330 core

in vec4 vColor;
out vec4 FragColor;

void main()
{
    vec4 color = vColor;

    FragColor = color;
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
