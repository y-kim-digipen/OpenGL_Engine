//
// Created by yoonki on 10/23/21.
//

#ifndef ENGINE_UBO_H
#define ENGINE_UBO_H


#include <cstddef>
#include <GL/glew.h>

class UBO {

public:
    ~UBO();

    void createUBO(const size_t byteSize, GLenum usageHint = GL_STREAM_DRAW);
    void bindUBO() const;
    void setBufferData(const size_t offset, const void* ptrData, const size_t dataSize);
    void bindBufferBaseToBindingPoint(const GLuint bindingPoint);
    GLuint getBufferID() const;
    void deleteUBO();

private:
    GLuint _bufferID{ 0 };
    size_t _byteSize;

    bool _isBufferCreated = false;
};


#endif //ENGINE_UBO_H
