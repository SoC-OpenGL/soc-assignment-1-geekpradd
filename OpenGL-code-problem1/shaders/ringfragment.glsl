#version 330 core
out vec4 output;
uniform int black;

void main(){
    output = (black ? vec4(0.0f, 0.0f, 0.0f, 0.0f) : vec4(1.0f, 0.5f, 0.2f, 1.0f));
}