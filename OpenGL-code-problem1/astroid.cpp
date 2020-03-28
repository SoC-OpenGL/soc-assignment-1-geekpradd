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
float *vertices;
float a = 0.5f;
int width = 800;
int height = 600;
float aspect_ratio = ((float) width)/height;

void genVertices(){
  int i = 0; float angle = 0;
  float pi = atan(1)*4;
  float increm = 2*pi/no_of_segments;
  while(i<6*no_of_segments){
    vertices[i] = a*cos(angle)*cos(angle)*cos(angle);i++;
    vertices[i] = a*sin(angle)*sin(angle)*sin(angle)*aspect_ratio;i++;
    vertices[i] = a*cos(angle+increm)*cos(angle+increm)*cos(angle+increm); i++;
    vertices[i] = a*sin(angle+increm)*sin(angle+increm)*sin(angle+increm)*aspect_ratio; i++;
    vertices[i] = 0.0f; i++;
    vertices[i] = 0.0f; i++;
    angle += increm;
  } 
}

int main(){
    vertices = new float[6*no_of_segments];
    genVertices();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* w = glfwCreateWindow(width, height, "Disc", NULL, NULL);

    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(w, reshape_viewport);
    glfwSetKeyCallback(w, key_callback);

    Shader *shdr = new Shader("shaders/vertexshader.glsl", "shaders/discfragment.glsl");
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint VBO; // vertex buffer object. stores on gpu buffer
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    std::cout << sizeof(vertices) << std::endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(6*no_of_segments), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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