//
//  ShaderTools.cpp
//  HelloTriangle
//
//  Created by alfa suni on 25/10/19.
//  Copyright © 2019 alfa suni. All rights reserved.
//

#include "ShaderTools.hpp"

const std::string ShaderTools::readFromFile(const std::string shaderFile)
{
    std::string strShader, strResult;
    std::ifstream myfile;
    
    myfile.open(shaderFile);
    
    if (myfile.is_open()) {
        strResult = "";
        while (!myfile.eof()) {
            getline(myfile, strShader);
            //            strResult += strShader + "\n";
            strResult.append(strShader + "\n");
        }
        
        myfile.close();
    }
    
    return strResult;
}

GLuint ShaderTools::CreateShader(GLenum eShaderType, const std::string &strShaderFile)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);
    
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        const char *strShaderType = NULL;
        switch(eShaderType)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER_EXT: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        
        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }
    
    return shader;
}

GLuint ShaderTools::CreateProgram(const std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();
    
    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glAttachShader(program, shaderList[iLoop]);
    
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    
    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glDetachShader(program, shaderList[iLoop]);
    
    return program;
}


void ShaderTools::InitializeProgram()
{
    std::vector<GLuint> shaderList;
    
    shaderList.push_back(CreateShader(GL_VERTEX_SHADER, readFromFile(strVertexShader)));
    shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, readFromFile(strFragmentShader)));
    
    theProgram = CreateProgram(shaderList);
    
    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}
