/************************************************************************
* Project: TextureMapping
* Function: Free Image Wrapper
*************************************************************************
* Author: Alfa
*************************************************************************
*
* Copyright 2010 by Alfa Faridh Suni
*
************************************************************************/

#include "NFreeImage.h"

NFreeImage::NFreeImage() : m_pImage(0)
{
}

bool NFreeImage::Load(const std::string &i_rFilename)
{
    Unload();

    FREE_IMAGE_FORMAT FreeImageFormat = FreeImage_GetFileType(i_rFilename.c_str(), 0);

    if(FreeImageFormat == FIF_UNKNOWN)
    {
        FreeImageFormat = FreeImage_GetFIFFromFilename(i_rFilename.c_str());

    }

    if(FreeImageFormat == FIF_UNKNOWN)
    {
        return false;
    }

    if(FreeImage_FIFSupportsReading(FreeImageFormat));
    {
        m_pImage = FreeImage_Load(FreeImageFormat, i_rFilename.c_str());
    }

    return m_pImage != 0;
}

unsigned int NFreeImage::Width() const
{
    return m_pImage ? FreeImage_GetWidth(m_pImage) : 0;
}

unsigned int NFreeImage::Height() const
{
    return m_pImage ? FreeImage_GetHeight(m_pImage) : 0;
}

unsigned int NFreeImage::BitsPerPixel() const
{
    return m_pImage ? FreeImage_GetBPP(m_pImage) : 0;
}

const BYTE* NFreeImage::Bits() const
{
    return m_pImage ? FreeImage_GetBits(m_pImage) : 0;
}

void NFreeImage::Unload()
{
    if(m_pImage)
    {
        FreeImage_Unload(m_pImage);
        m_pImage = 0;
    }
}


NFreeImage::~NFreeImage()
{
    Unload();
}













