//
// Created by yoonki on 10/31/21.
//

#ifndef ENGINE_TEXTUREMANAGER_H
#define ENGINE_TEXTUREMANAGER_H
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include "TextureObject.h"

class TextureManager {
public:
    int CreateTextureFromFile(const std::string& file, const std::string& textureName, GLenum type, GLint textureUnit);

private:
    TextureObject* CreateTexture(const std::string& textureName, GLint width, GLint height, GLenum textureType, GLint textureUnit);
};


#endif //ENGINE_TEXTUREMANAGER_H
