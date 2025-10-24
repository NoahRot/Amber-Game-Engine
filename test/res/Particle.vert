#version 330 core

layout(location = 0) in vec2 aPosition;  // Particle world position
layout(location = 1) in vec4 aColor;     // RGBA
layout(location = 2) in float aSize;     // Size in world units

uniform mat4 u_mvp;                       // Model-View-Projection matrix

out vec4 vColor;

void main()
{
    gl_Position = u_mvp * vec4(aPosition, 0.0, 1.0);
    gl_PointSize = aSize;
    vColor = aColor;
}