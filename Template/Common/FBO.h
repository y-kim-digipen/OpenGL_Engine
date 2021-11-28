//
// Created by yoonki on 11/20/21.
//

#ifndef ENGINE_FBO_H
#define ENGINE_FBO_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <map>
#include <vector>
class TextureObject;
class FBO {
public:
    void Init(GLuint width, GLuint height);
    void SetAttachment(GLenum slot, TextureObject* texture, GLuint level = 0);
    void SetDepthAttachment();
    void UseDrawBuffers();

    std::pair<GLuint, GLuint> GetFBOSize();
    GLuint GetFBOHandle();
    TextureObject *GetTextureAttachment(GLenum slot);
    std::string GetAttachmentTextureName(GLenum slot);
private:
    GLuint mFBOHandle;
    GLuint mDepthHandle;

    GLuint mFBOWidth, mFBOHeight;

    std::map<GLenum, TextureObject*> mAttachments;
    std::vector<GLenum> mDrawBuffers;
};


#endif //ENGINE_FBO_H
