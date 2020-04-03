#version 330 core
out vec4 output;
in vec2 texCoord;

uniform bool black;
uniform sampler2D text;

void main(){
    output = (black ? vec4(0.0f, 0.0f, 0.0f, 0.0f) : texture(text, texCoord));
}