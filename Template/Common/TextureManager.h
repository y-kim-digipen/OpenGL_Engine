//
// Created by yoonki on 10/31/21.
//

#ifndef ENGINE_TEXTUREMANAGER_H
#define ENGINE_TEXTUREMANAGER_H
#include <string>
#include <map>
#include <GL/glew.h>
#include <GL/gl.h>
#include "TextureObject.h"

class TextureManager {
public:
    int CreateTextureFromFile(const std::string& file, const std::string& textureName, GLenum type, GLint textureUnit);
    TextureObject* FindTextureByName(const std::string& name);
    void BindTexture(TextureObject* pTexture);
private:
    TextureObject* CreateTexture(const std::string& textureName, GLint width, GLint height, GLenum textureType, GLint textureUnit);
    void SetSamplerClampingProperties(GLuint samplerID, GLenum clampProp, GLenum mipmapProp);

    //todo change this to shared ptr
    std::map<std::string, TextureObject*> mTextureObjects;
    std::map<TextureObject*, GLuint> mSamplerObjects;
};


#endif //ENGINE_TEXTUREMANAGER_H
