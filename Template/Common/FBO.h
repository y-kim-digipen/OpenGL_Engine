//
// Created by yoonki on 11/20/21.
//

#ifndef ENGINE_FBO_H
#define ENGINE_FBO_H


#include <GL/gl.h>
#include <vector>
#include <map>

class TextureObject;
class FBO {
public:
    void Init(GLint width, GLint height);
    bool AddAttachment(GLint slot, TextureObject* pTextureObject, GLuint level);
    void AddDepthAttachment();
    void UseDrawBuffers();
    ~FBO();
private:
    GLuint mFBOHandle;
    GLuint mDepthRenderHandle;
    GLuint m_width, m_height;
    std::vector<GLenum> mDrawBuffers;
    std::map<GLenum, TextureObject*> mAttachments;
};


#endif //ENGINE_FBO_H
