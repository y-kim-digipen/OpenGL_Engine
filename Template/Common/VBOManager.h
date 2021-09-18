//
// Created by yoonki on 9/17/21.
//

#ifndef ENGINE_VERTEXBUFFERMANAGER_H
#define ENGINE_VERTEXBUFFERMANAGER_H
#include <map>
#include <GL/gl.h>

class VertexBufferManager {
private:
    //VAOID, <meshName, <attribname, >>>
    std::map<GLuint, std::map<std::string, std::map<std::string, std::pair<GLint, GLint>>>> mAttribOffsets;

};


#endif //ENGINE_VERTEXBUFFERMANAGER_H
