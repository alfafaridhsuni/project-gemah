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
#include "NTexture.h"

NTexture::NTexture() : m_Texture(0)
{
}

bool NTexture::Load(const std::string &i_rFilename)
{
    NFreeImage FreeImage;
    if(!FreeImage.Load(i_rFilename))
    {
        return false;
    }

    glGenTextures(1, &m_Texture);

    glBindTexture(GL_TEXTURE_2D, m_Texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage.Width(), FreeImage.Height(), 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage.Bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

bool NTexture::LoadMipMaps(const std::string &i_rFilename, float i_LodBias = 0.0f)
{
    NFreeImage FreeImage;
    if(!FreeImage.Load(i_rFilename))
    {
        return false;
    }

    glGenTextures(1, &m_Texture);

    glBindTexture(GL_TEXTURE_2D, m_Texture);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, FreeImage.Width(), FreeImage.Height(), GL_BGR, GL_UNSIGNED_BYTE, FreeImage.Bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, i_LodBias);

    return true;
}

void NTexture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}








