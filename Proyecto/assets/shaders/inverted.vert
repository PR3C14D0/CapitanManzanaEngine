#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 vColor;

out vec4 vertexColor;

void main() {
    vec4 invertedPos = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    gl_Position = invertedPos;
    vertexColor = vColor;
}