#version 330 core
out vec4 output;
in vec2 texCoord;

uniform sampler2D text;

void main(){
    output = texture(text, texCoord);
}