#ifndef NFREEIMAGE_H_INCLUDED
#define NFREEIMAGE_H_INCLUDED

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

#include <FreeImage.h>
#include <string>

class NFreeImage
{
public:
    NFreeImage();
    ~NFreeImage();
    bool Load(const std::string &i_rFilename);
    unsigned int Width() const;
    unsigned int Height() const;
    unsigned int BitsPerPixel() const;
    const BYTE* Bits() const;
    void Unload();

private:
    FIBITMAP* m_pImage;

};



#endif // NFREEIMAGE_H_INCLUDED
