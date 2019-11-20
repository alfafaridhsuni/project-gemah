//
//  MyRenderer.hpp
//  HelloTriangle
//
//  Created by alfa suni on 25/10/19.
//  Copyright © 2019 alfa suni. All rights reserved.
//

#ifndef MyRenderer_hpp
#define MyRenderer_hpp

#include "ShaderTools.hpp"
#include "GLFW/glfw3.h"

class MyRenderer {
    GLuint vertexBufferObject;
    GLuint vao;
    ShaderTools *st = new ShaderTools();
    
public:
    void InitializeVertexBuffer();
    void init();
    void display();
    void render();
    void reshape(GLFWwindow *window);

};


#endif /* MyRenderer_hpp */
