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
int array_size = 8*8*2*3*3;
float length = 1.00f;
float x_topleft = -0.5f;
float y_topleft = 0.5f;
float *vertices;
int width = 800;
int height = 600;
float aspect_ratio = ((float) width)/height;

void genVertices(){
    vertices = new float[array_size];
    int i = 0;
    float red = 1.0f;
    float step = length/8;
    for (int k=0; k<8; ++k){
        for (int j=0; j<8;++j){
            float topl_x = x_topleft + j*step; float topl_y = y_topleft - k*step;
            float topr_x = topl_x + step; float topr_y = topl_y;
            float bottoml_x = topl_x;  float bottoml_y = topl_y - step;
            float bottomr_x = topr_x; float bottomr_y = bottoml_y;
            vertices[i] = topl_x; i++; vertices[i] = topl_y*aspect_ratio; i++; vertices[i] = red; i++;
            vertices[i] = topr_x; i++; vertices[i] = topr_y*aspect_ratio; i++; vertices[i] = red; i++;
            vertices[i] = bottoml_x; i++; vertices[i] = bottoml_y*aspect_ratio; i++; vertices[i] = red; i++;
            vertices[i] = topr_x; i++; vertices[i] = topr_y*aspect_ratio; i++; vertices[i] = red; i++;
            vertices[i] = bottoml_x; i++; vertices[i] = bottoml_y*aspect_ratio; i++; vertices[i] = red; i++;
            vertices[i] = bottomr_x; i++; vertices[i] = bottomr_y*aspect_ratio; i++; vertices[i] = red; i++;

            if (red == 1.0f)
                red = 0.0f;
            else
                red = 1.0f;
        }
        if (red == 1.0f)
            red = 0.0f;
        else
            red = 1.0f;
    }
}
int main(){
    genVertices();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* w = glfwCreateWindow(width, height, "Chessboard", NULL, NULL);

    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(w, reshape_viewport);
    glfwSetKeyCallback(w, key_callback);

    Shader *shdr = new Shader("shaders/chessboardvertexshader.glsl", "shaders/fragment.glsl");
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint VBO; // vertex buffer object. stores on gpu buffser
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*array_size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(w)){
        glClear(GL_COLOR_BUFFER_BIT);  
        shdr->use();
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, array_size/3);
        glfwSwapBuffers(w);
        glfwPollEvents();
    } 

    glfwTerminate();
    return 0;

}