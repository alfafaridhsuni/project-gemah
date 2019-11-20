//
//  MyRenderer.cpp
//  HelloTriangle
//
//  Created by alfa suni on 25/10/19.
//  Copyright © 2019 alfa suni. All rights reserved.
//

#include "MyRenderer.hpp"

const float vertexData[] = {
    // position
//     0.25f, 0.25f,  0.0f, 1.0f,
//    -0.25f,  0.25f, 0.0f, 1.0f,
//    -0.25f, -0.25f, 0.0f, 1.0f,
//
//     0.25f, 0.25f,  0.0f, 1.0f,
//     0.25f, -0.25f, 0.0f, 1.0f,
//    -0.25f, -0.25f, 0.0f, 1.0f,
    
    // color
//    1.0f, 0.0f, 0.0f, 1.0f,
//    0.0f, 1.0f, 0.0f, 1.0f,
//    0.0f, 0.0f, 1.0f, 1.0f,
//
//    0.0f, 1.0f, 0.0f, 1.0f,
//    0.0f, 1.0f, 0.0f, 1.0f,
//    0.0f, 0.0f, 1.0f, 1.0f
    
     0.0f,    0.5f, 0.0f, 1.0f,
     0.5f, -0.366f, 0.0f, 1.0f,
    -0.5f, -0.366f, 0.0f, 1.0f,
     1.0f,    0.0f, 0.0f, 1.0f,
     0.0f,    1.0f, 0.0f, 1.0f,
     0.0f,    0.0f, 1.0f, 1.0f
};

void MyRenderer::InitializeVertexBuffer()
{
    glGenBuffers(1, &vertexBufferObject);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void MyRenderer::init()
{
    st->InitializeProgram();
    InitializeVertexBuffer();
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void MyRenderer::display()
{
    glUseProgram(st->theProgram);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}

void MyRenderer::reshape(GLFWwindow *window)
{
    float ratio;
    int width, height;
    
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void MyRenderer::render()
{
    GLFWwindow* window;
    
    
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    window = glfwCreateWindow(800, 800, "Hello GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);
    
    init();
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window)) {
        reshape(window);
        display();
        glfwSetKeyCallback(window, key_callback);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
}
