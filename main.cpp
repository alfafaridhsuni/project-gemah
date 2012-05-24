// Transparency
// Program ini menampilkan efek transparan pada texture
// Image Loadernya menggunakan library tambahan yaitu SOIL (Simple OpenGL Image Library)
// Untuk mendapatkan efek transparan caranya dengan melakukan Blending dengan warna putih dan 50% Alpha

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "SOIL.h"

#include <GL/glut.h>

float z_pos = -5.0f;
float xRot, yRot, zRot;
float rot = 0.0f;


GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

// storage for one texture
GLuint tex_2d;

GLuint tex_2d1;
GLuint tex_2d2;
GLuint tex_2d3;
GLuint tex_2d4;
GLuint tex_2d5;
GLuint tex_2d6;

/* storage for one texture  */
GLuint texture[1];

GLuint LoadGLTextures(int i, char* filename);
void drawCube();

void init();
void myKeyboard(unsigned char, int, int);
void myDisplay(void);
void myTimeOut(int);
void resize(int, int);


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Transparency");

    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(resize);
    glutTimerFunc(100, myTimeOut, 0);
    init();

    glutMainLoop();



    return 0;
}

GLuint LoadGLTextures(char* filename)                             // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    tex_2d = SOIL_load_OGL_texture(filename,
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_MIPMAPS |
                                   SOIL_FLAG_INVERT_Y |
                                   SOIL_FLAG_NTSC_SAFE_RGB |
                                   SOIL_FLAG_COMPRESS_TO_DXT);

    /* check for an error during the load process */
    if(tex_2d == 0)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    // Typical Texture Generation Using Data From The Bitmap
    //glBindTexture(GL_TEXTURE_2D, tex_2d);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);



    return tex_2d;                                        // Return Success
}

void init()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT1);


}

void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '<':
        case ',':
                z_pos -= 0.1f;
                break;
        case '>':
        case '.':
                z_pos += 0.1f;
                break;

        case 27:
                exit(0);
                break;
        default:
                break;
    }
}
void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, z_pos);
    glRotatef(xRot,1.0f,0.0f,0.0f);		// Rotate On The X Axis
    glRotatef(yRot,0.0f,1.0f,0.0f);		// Rotate On The Y Axis
    glRotatef(zRot,0.0f,0.0f,1.0f);		// Rotate On The Z Axis

//    glEnable(GL_BLEND);               // enabling BLENDING state
    //glDisable(GL_DEPTH_TEST);

    drawCube();

//    xRot+=15.0f;		                // X Axis Rotation
    yRot+=15.0f;		                // Y Axis Rotation
//    zRot+=15.0f;		                // Z Axis Rotation
    glFlush();
    glutSwapBuffers();


}
void myTimeOut(int id)
{

    rot += 5.0f;
    glutPostRedisplay();
    glutTimerFunc(100, myTimeOut, 0);
}

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 1.0, 300.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void drawCube()
{
    glBindTexture(GL_TEXTURE_2D, LoadGLTextures("NeHe.bmp"));
    glBegin(GL_QUADS);
        // Front Face
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
    glEnd();

//    glBindTexture(GL_TEXTURE_2D, LoadGLTextures("NeHe.bmp"));
    glBegin(GL_QUADS);
        // Back Face
        glNormal3f( 0.0f, 0.0f,-1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, LoadGLTextures("floor.tga"));
    glBegin(GL_QUADS);
        // Top Face
        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glEnd();

//    glBindTexture(GL_TEXTURE_2D, LoadGLTextures("floor.tga"));
    glBegin(GL_QUADS);
        // Bottom Face
        glNormal3f( 0.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, LoadGLTextures("background.bmp"));
    glBegin(GL_QUADS);
        // Right face
        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glEnd();


    glEnable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);          //  Full Brightness. 50% Alpha
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBindTexture(GL_TEXTURE_2D, LoadGLTextures("background.bmp"));
    glBegin(GL_QUADS);
        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
    glDisable(GL_BLEND);
}










