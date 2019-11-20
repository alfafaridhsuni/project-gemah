//
//  ShaderTools.hpp
//  HelloTriangle
//
//  Created by alfa suni on 25/10/19.
//  Copyright © 2019 alfa suni. All rights reserved.
//

#ifndef ShaderTools_hpp
#define ShaderTools_hpp

#include <vector>
#include <fstream>

#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

class ShaderTools {

public:
    GLuint theProgram;
    
    const std::string strVertexShader =
    "/Users/alfasuni/Documents/PROGRAMMING/HelloTriangle/HelloTriangle/Colored.vert";
    //("#version 150\n in vec2 position; void main() {gl_Position = vec4(position, 0.0, 1.0);}");
    
    const std::string strFragmentShader =
    "/Users/alfasuni/Documents/PROGRAMMING/HelloTriangle/HelloTriangle/Colored.frag";
    //("#version 150\n out vec4 fragColor; void main() {fragColor = vec4(1.0, 0.0, 0.0, 1.0);}");

    const std::string readFromFile(const std::string shaderFile);
    GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
    GLuint CreateProgram(const std::vector<GLuint> &shaderList);
    void InitializeProgram();
};

#endif /* ShaderTools_hpp */
