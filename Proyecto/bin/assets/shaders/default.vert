#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 vColor;

out vec4 vertexColor;

uniform mat4 modelView;  // model-view matrix
uniform mat4 projection; // projection

void main() {
    gl_Position = projection * modelView * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vColor;
}