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
    "/Users/alfasuni/Documents/PROGRAMMING/TwoTriangle/TwoTriangle/Colored.vert";
    
    const std::string strFragmentShader =
    "/Users/alfasuni/Documents/PROGRAMMING/TwoTriangle/TwoTriangle/Colored.frag";
    
    const std::string readFromFile(const std::string shaderFile);
    void InitializeProgram();
    
private:
    GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
    GLuint CreateProgram(const std::vector<GLuint> &shaderList);
};

#endif /* ShaderTools_hpp */
