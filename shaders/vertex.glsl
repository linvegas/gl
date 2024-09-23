#version 330 core

layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 acolor;

out vec3 ourColor;

void main() {
    gl_Position = vec4(apos.xyz, 1.0);
    ourColor = acolor;
};
