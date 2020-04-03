#version 330 core
in vec3 colorOut;
out vec4 output;

void main(){
    output = vec4(colorOut, 1.0);
}