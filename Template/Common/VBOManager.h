/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: VBOManager.h
Purpose: Header file of VBOManager
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef ENGINE_VBOMANAGER_H
#define ENGINE_VBOMANAGER_H
#include <map>
#include <memory>

#include <GL/gl.h>

class Mesh;
class VBOManager {
public:
    void SetUpVBO(Mesh* pMesh);
    void CleanUp();
    std::pair<std::map<std::string, GLuint>, GLuint>& GetVBOInfo(std::shared_ptr<Mesh> pMesh);
private:
    //<MeshName, <<name, VBO>, EBO>>
    std::map<std::string, std::pair<std::map<std::string, GLuint>, GLuint>> mVBOInfos;
};


#endif //ENGINE_VBOMANAGER_H
