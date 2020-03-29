#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "include/utility.hpp"
#include "include/shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

void reshape_viewport(GLFWwindow *w, int width, int height){
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
  }

int no_of_segments = 1000;
float *vertices;
float radius = 0.5f;
int width = 800;
int height = 600;
float aspect_ratio = ((float) width)/height;

float* texture_coords;
void genVertices(){
  int i = 0; float angle = 0;
  float pi = atan(1)*4;
  float increm = 2*pi/no_of_segments;
  while(i<6*no_of_segments){
    vertices[i] = radius*cos(angle); i++;
    vertices[i] = radius*sin(angle)*aspect_ratio;i++;
    vertices[i] = radius*cos(angle+increm); i++;
    vertices[i] = radius*sin(angle+increm)*aspect_ratio; i++;
    vertices[i] = 0.0f; i++;
    vertices[i] = 0.0f; i++;

    for (int k=i-6; k<i; ++k){
      float denom = ((i-k)%2 ? (2*aspect_ratio) : 2.0f);
      texture_coords[k] = vertices[k]/denom + 0.5f;
    }
    angle += increm;
  } 
}
//
int main(){
  
    int wi, hi, nrChannels;
    unsigned char* data = stbi_load("textures/wall.jpg", &wi, &hi, &nrChannels, 0);
    vertices = new float[6*no_of_segments];
    texture_coords = new float[6*no_of_segments];
    genVertices();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* w = glfwCreateWindow(width, height, "Disc", NULL, NULL);

    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(w, reshape_viewport);
    glfwSetKeyCallback(w, key_callback);

    Shader *shdr = new Shader("shaders/vertexshader.glsl", "shaders/fragment.glsl");
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint VBO; // vertex buffer object. stores on gpu buffer
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    std::cout << sizeof(vertices) << std::endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(6*no_of_segments*2), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*(6*no_of_segments), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*(6*no_of_segments), sizeof(float)*(6*no_of_segments), texture_coords);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) (sizeof(float)*(6*no_of_segments)));
    glEnableVertexAttribArray(1);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wi, hi, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    while (!glfwWindowShouldClose(w)){
        glClear(GL_COLOR_BUFFER_BIT);  
        glBindVertexArray(VAO);
        shdr->use();
        
        glDrawArrays(GL_TRIANGLES, 0, 3*no_of_segments);
        glfwSwapBuffers(w);
        glfwPollEvents();
    } 

    glfwTerminate();
    return 0;

}