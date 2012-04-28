#ifndef NTEXTURE_H_INCLUDED
#define NTEXTURE_H_INCLUDED

/************************************************************************
* Project: TextureMapping
* Function: Create OpenGL Textures
*************************************************************************
* Author: Alfa
*************************************************************************
*
* Copyright 2010 by Alfa Faridh Suni
*
************************************************************************/
#include <GL/gl.h>
#include <GL/glu.h>
#include "NFreeImage.h"

class NTexture
{
public:
    NTexture();
    bool Load(const std::string &i_rFilename);
    bool LoadMipMaps(const std::string &i_rFilename, float i_LodBias);
    void Bind() const;

private:
    GLuint m_Texture;

};

#endif // NTEXTURE_H_INCLUDED
