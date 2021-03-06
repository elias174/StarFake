#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#include <GL/glut.h>

#include <FreeImage.h>
#include <map>

class TextureManager
{
public:
    static TextureManager* Inst();
    virtual ~TextureManager();

    //load a texture an make it the current texture
    //if texID is already in use, it will be unloaded and replaced with this texture
    GLuint LoadTexture(const char* filename,	//where to load the file from
        GLenum image_format = GL_RGB,		//format the image is in
        GLint internal_format = GL_RGB,		//format to store the image in
        GLint level = 0,					//mipmapping level
        GLint border = 0);					//border size


protected:
    TextureManager();
    TextureManager(const TextureManager& tm);
    TextureManager& operator=(const TextureManager& tm);

    static TextureManager* m_inst;
};


#endif // TEXTUREMANAGER_H
