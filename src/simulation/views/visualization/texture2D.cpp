#include <simulation/views/visualization/texture2D.hpp>


Texture2D::Texture2D(const int width, const int height, const float *data, const InternalFormat internalFormat,
                     const InputDataFormat inputFormat):
    Texture2D(width, height, internalFormat)
{
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, inputFormat, GL_FLOAT, data);
}


Texture2D::Texture2D(int width, const int height, const InternalFormat internalFormat):
    width(width), height(height), internalFormat(internalFormat)
{
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


void Texture2D::Update(const float *data, const InputDataFormat inputFormat) const
{
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, inputFormat, GL_FLOAT, data);
}


void Texture2D::ChangeSize(const int texWidth, const int texHeight, const float *data, const InputDataFormat inputFormat)
{
    width = texWidth;
    height = texHeight;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, inputFormat, GL_FLOAT, data);
}


Texture2D::~Texture2D()
{
    glDeleteTextures(1, &id);
}
