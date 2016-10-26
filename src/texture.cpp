#include "texture.h"
#include <cmath>
#include <iostream>




Texture::Texture()
{

}

typedef std::bitset<8> BYTE;
typedef std::bitset<8> byte;

struct RGBTRIPLE {
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
};

struct BITMAPFILEHEADER
{
   unsigned short type;
   unsigned int   size;
   unsigned short reserved1;
   unsigned short reserved2;
   unsigned int   off_bits;

   unsigned int struct_size()
   {
      return sizeof(type)     +
            sizeof(size)      +
            sizeof(reserved1) +
            sizeof(reserved2) +
            sizeof(off_bits);
   }
};

struct BITMAPINFOHEADER
{
   unsigned int   size;
   unsigned int   biWidth;
   unsigned int   biHeight;
   unsigned short planes;
   unsigned short bit_count;
   unsigned int   compression;
   unsigned int   size_image;
   unsigned int   x_pels_per_meter;
   unsigned int   y_pels_per_meter;
   unsigned int   clr_used;
   unsigned int   clr_important;

   unsigned int struct_size()
   {
      return sizeof(size)             +
             sizeof(biWidth)            +
             sizeof(biHeight)           +
             sizeof(planes)           +
             sizeof(bit_count)        +
             sizeof(compression)      +
             sizeof(size_image)       +
             sizeof(x_pels_per_meter) +
             sizeof(y_pels_per_meter) +
             sizeof(clr_used)         +
             sizeof(clr_important);
   }
};

GLuint Texture::create1DTexture(std::vector<GLubyte>& rgbaValues)
{
    GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_1D, textureID);
    glTexStorage1D(GL_TEXTURE_1D, 1, GL_RGBA8, rgbaValues.size()*sizeof (GLubyte) / 4);
    glTexSubImage1D(GL_TEXTURE_1D, 0, 0, rgbaValues.size()*sizeof (GLubyte) / 4, GL_RGBA, GL_UNSIGNED_BYTE, rgbaValues.data());
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_1D, 0);

    return textureID;
}


GLuint Texture::create2DTexture(std::vector<unsigned char>& image, unsigned int width, unsigned int height)
{
	GLuint textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return textureID;
}
/*
extern "C" {
  #include "bmpread.h" //a C header, so wrap it in extern "C"
  int bmpread(const char * bmp_file, unsigned int flags, bmpread_t * p_bmp_out);
  void bmpread_free(bmpread_t * p_bmp);

GLuint  Texture::LoadBitmap(const char *filename)
{
  GLuint texture = 0;
  bmpread_t bitmap;

 if(!bmpread(filename, 0, &bitmap))
 {
     fprintf(stderr, "%s: error loading bitmap file\n", filename);
     exit(1);
 }

 /* At this point, bitmap.width and .height hold the pixel dimensions of the
  * file, and bitmap.rgb_data holds the raw pixel data in RGB triplets.
  */
/*
 glGenTextures(1, &texture);
 glBindTexture(GL_TEXTURE_2D, texture);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 glTexImage2D(GL_TEXTURE_2D, 0, 3, bitmap.width, bitmap.height, 0,
              GL_RGB, GL_UNSIGNED_BYTE, bitmap.rgb_data);

 bmpread_free(&bitmap);

 return texture;
}
}*/



void Texture::bind2DTexture(GLuint _program, GLuint _textureID, std::string varName)
{
	glActiveTexture(GL_TEXTURE0 + _textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glUniform1i(glGetUniformLocation(_program, varName.c_str()), _textureID);
}

void Texture::bind1DTexture(GLuint _program, GLuint _textureID, std::string varName)
{
	glActiveTexture(GL_TEXTURE0 + _textureID);
	glBindTexture(GL_TEXTURE_1D, _textureID);
	glUniform1i(glGetUniformLocation(_program, varName.c_str()), _textureID);
}

void Texture::unbind1DTexture()
{
	glBindTexture(GL_TEXTURE_1D, 0);
}

void Texture::unbind2DTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
