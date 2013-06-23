//
//  main.cpp
//  HelloTriangle
//
//  Created by alfa suni on 6/21/13.
//  Copyright (c) 2013 alfa suni. All rights reserved.
//
#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
//#include <glload/gl_3_2_comp.h>
#include <iostream>
#include <fstream>
#include <GLUT/GLUT.h>

const std::string readFromFile(const std::string shaderFile)
{
    std::string strShader, strResult;
    std::ifstream myfile;
    
    myfile.open(shaderFile);
    
    if (myfile.is_open()) {
        while (!myfile.eof()) {
            getline(myfile, strShader);
            strResult += strShader + "\n";
        }
        
        myfile.close();
    }
    
    const std::string result = strResult;
    
    return result;
}

GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
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

GLuint CreateProgram(const std::vector<GLuint> &shaderList)
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

GLuint theProgram;

const std::string strVertexShader = "/Users/alfafaridh/Programming/OpenGL/Learning Modern 3D Graphics Programming/HelloTriangle/HelloTriangle/hello.vert";
//("#version 120\nvoid main()\n{\ngl_Position = gl_Vertex;\n}\n");

const std::string strFragmentShader = "/Users/alfafaridh/Programming/OpenGL/Learning Modern 3D Graphics Programming/HelloTriangle/HelloTriangle/fragment.frag";
//("#version 120\nvoid main()\n{\ngl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n}\n");

void InitializeProgram()
{
	std::vector<GLuint> shaderList;    

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, readFromFile(strVertexShader)));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, readFromFile(strFragmentShader)));
    
	theProgram = CreateProgram(shaderList);
    
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

const float vertexPositions[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};

GLuint positionBufferObject;
GLuint vao;


void InitializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);
    
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVertexBuffer();
    
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    
	glUseProgram(theProgram);
    
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
	glDrawArrays(GL_TRIANGLES, 0, 3);
    
	glDisableVertexAttribArray(0);
	glUseProgram(0);
    
	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
        case 27:
//            glutLeaveMainLoop();
            glutLeaveGameMode();
            return;
	}
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    
	int width = 500;
	int height = 500;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
	displayMode = defaults(displayMode, width, height);
    
	glutInitDisplayMode (displayMode);
//	glutInitContextVersion (3, 3);
//	glutInitContextProfile(GLUT_CORE_PROFILE);
//#ifdef DEBUG
//	glutInitContextFlags(GLUT_DEBUG);
//#endif
	glutInitWindowSize (width, height);
	glutInitWindowPosition (300, 200);
    glutCreateWindow (argv[0]);
    
//	glload::LoadFunctions();
    
//	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    
//	if(!glload::IsVersionGEQ(3, 3))
//	{
//		printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3 to run this tutorial.\n",
//               glload::GetMajorVersion(), glload::GetMinorVersion());
//		glutDestroyWindow(window);
//		return 0;
//	}
//    
//	if(glext_ARB_debug_output)
//	{
//		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
//		glDebugMessageCallbackARB(DebugFunc, (void*)15);
//	}
    
	init();
    
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    
    
	return 0;
}

