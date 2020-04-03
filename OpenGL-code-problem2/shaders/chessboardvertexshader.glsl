#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in float red;
out vec3 colorOut;

void main(){
    gl_Position =  vec4(pos, 0.0f, 1.0f);
    if (red == 1.0f)
        colorOut = vec3(1.0f, 0.0f, 0.0f);
    else
        colorOut = vec3(1.0f, 1.0f, 1.0f);
}