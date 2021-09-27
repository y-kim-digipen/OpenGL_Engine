//
// Created by yoonki on 9/17/21.
//

#ifndef ENGINE_VBOMANAGER_H
#define ENGINE_VBOMANAGER_H
#include <map>
#include <memory>

#include <GL/gl.h>

class Mesh;
class VBOManager {
public:
    void SetUpVBO(Mesh* pMesh);
    std::pair<std::map<std::string, GLuint>, GLuint>& GetVBOInfo(std::shared_ptr<Mesh> pMesh);
private:
    //<MeshName, <<name, VBO>, EBO>>
    std::map<std::string, std::pair<std::map<std::string, GLuint>, GLuint>> mVBOInfos;
};


#endif //ENGINE_VBOMANAGER_H
