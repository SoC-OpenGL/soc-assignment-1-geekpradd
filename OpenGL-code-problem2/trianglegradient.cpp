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

float vertices[] = {
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
}; 


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* w = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);

    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(w, reshape_viewport);
    glfwSetKeyCallback(w, key_callback);

    Shader *shdr = new Shader("shaders/trianglevertexshader.glsl", "shaders/fragment.glsl");
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint VBO; // vertex buffer object. stores on gpu buffer
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(w)){
        glClear(GL_COLOR_BUFFER_BIT);  
        shdr->use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(w);
        glfwPollEvents();
    } 

    glfwTerminate();
    return 0;

}