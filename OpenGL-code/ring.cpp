#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "include/utility.hpp"
#include "include/shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
float *vertices_out;
float *vertices_in;
float radius = 0.5f;
float gap = 0.005f;
int width = 800;
int height = 600;
float aspect_ratio = ((float) width)/height;
int i = 0;

void genVertices(float* target){
  int i = 0; float angle = 0;
  float pi = atan(1)*4;
  float increm = 2*pi/no_of_segments;
  while(i<9*no_of_segments){
    target[i] = radius*cos(angle);i++;
    target[i] = radius*sin(angle)*aspect_ratio;i++;
    target[i] = 0.0f; i++;
    target[i] = radius*cos(angle+increm); i++;
    target[i] = radius*sin(angle+increm)*aspect_ratio; i++;
    target[i] = 0.0f; i++;
    target[i] = 0.0f; i++;
    target[i] = 0.0f; i++;
    target[i] = 0.0f; i++;
    angle += increm;
  } 
}

int main(){
    vertices_out = new float[9*no_of_segments];
    vertices_in =  new float[9*no_of_segments];
    genVertices(vertices_out);
    radius -= gap;
    genVertices(vertices_in);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* w = glfwCreateWindow(width, height, "Ring", NULL, NULL);

    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(w, reshape_viewport);
    glfwSetKeyCallback(w, key_callback);

    Shader *shdr = new Shader("shaders/vertexshader.glsl", "shaders/ringfragment.glsl");
    
    GLuint VAO_out, VAO_in;
    glGenVertexArrays(1, &VAO_out); glGenVertexArrays(1, &VAO_in);
    GLuint VBO_out, VBO_in; // vertex buffer object. stores on gpu buffer
    glGenBuffers(1, &VBO_out); glGenBuffers(1, &VBO_in);

    glBindVertexArray(VAO_out); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO_out);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(9*no_of_segments), vertices_out, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(VAO_in);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_in);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(9*no_of_segments), vertices_in, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(w)){
        glClear(GL_COLOR_BUFFER_BIT);  
        glBindVertexArray(VAO_out);
        shdr->use();
        shdr->setInt("black", 0);
        glDrawArrays(GL_TRIANGLES, 0, 3*no_of_segments);

        glBindVertexArray(VAO_in);
        shdr->setInt("black", 1);
        glDrawArrays(GL_TRIANGLES, 0, 3*no_of_segments);

        glfwSwapBuffers(w);
        glfwPollEvents();
    } 

    glfwTerminate();
    return 0;

}