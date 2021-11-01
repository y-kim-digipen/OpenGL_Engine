//
// Created by yoonki on 10/31/21.
//

#include "TextureManager.h"

#include <iostream>



#include "SOIL.h"

int TextureManager::CreateTextureFromFile(const std::string &file, const std::string &textureName, GLenum type,
                                          GLint TextureUnit) {
    GLint channel, width, height;
    std::cout << "[ Creating Texture \"" << file << " \"] " <<std::endl;
    GLubyte * img = SOIL_load_image(file.c_str(), &width, &height, &channel, SOIL_LOAD_AUTO);

    if(img == nullptr)
    {
        return -1;
    }

    glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

}

TextureObject *
TextureManager::CreateTexture(const std::string &textureName, GLint width, GLint height, GLenum textureType,
                              GLint textureUnit) {
    TextureObject* t = new TextureObject;
    GLuint textureHandle;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureHandle);

    return nullptr;
}
