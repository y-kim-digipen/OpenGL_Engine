//
// Created by pushpak on 10/5/18.
//

#ifndef SIMPLE_OBJ_SCENE_MESH_H
#define SIMPLE_OBJ_SCENE_MESH_H

#include <vector>

#include <glm/glm.hpp>
#include <GL/glut.h>

#include "ObjectComponents/ComponentBase.h"

class Mesh : public ComponentBase
{
public:
    friend class OBJReader;
    void SetupBuffer();
    void CleanUp();
    // Get attribute values buffer
    GLfloat *getVertexBuffer();             // attribute 0
    GLfloat *getVertexNormals();            // attribute 1
    GLfloat *getVertexUVs();                // attribute 2

    GLfloat *getVertexNormalsForDisplay();  // attribute 0

    [[nodiscard]] unsigned int getVertexBufferSize() const;
    [[nodiscard]] unsigned int getVertexCount() const;
    [[nodiscard]] unsigned int getVertexNormalCount() const;
    [[nodiscard]] unsigned int getVertexIndicesCount() const;

    // Get vertex index buffer
    GLuint *getIndexBuffer();
    [[nodiscard]] unsigned int getIndexBufferSize() const;
    [[nodiscard]] unsigned int getTriangleCount() const;

    glm::vec3   getModelScale();
    glm::vec3   getModelCentroid();
    glm::vec3   getCentroidVector( glm::vec3 vVertex );


    GLfloat  &  getNormalLength();
    void setNormalLength( GLfloat nLength );

    // initialize the data members
    void initData();

    // calculate vertex normals
    int calcVertexNormals(GLboolean bFlipNormals = false);

    // calculate the "display" normals
    void calcVertexNormalsForDisplay(GLboolean bFlipNormals = false);

    // calculate texture coordinates
    enum UVType { PLANAR_UV = 0,
                  CYLINDRICAL_UV,
                  SPHERICAL_UV,
                  CUBE_MAPPED_UV};

    int         calcUVs( Mesh::UVType uvType = Mesh::PLANAR_UV );
    glm::vec2   calcCubeMap( glm::vec3 vEntity );

    //todo add more if needed
    enum DrawType{  POINT = GL_POINT,
                    POINTS = GL_POINTS,
                    LINE = GL_LINE,
                    LINES = GL_LINES,
                    LINE_STRIP = GL_LINE_STRIP,
                    LINE_LOOP = GL_LINE_LOOP,
                    TRIANGLES = GL_TRIANGLES,
                    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
                    TRIANGLE_FAN = GL_TRIANGLE_FAN,
    };

    [[nodiscard]] DrawType GetDrawType() const;
    void SetDrawType(DrawType drawType);

    [[nodiscard]] GLint GetVAOID() const;
    [[nodiscard]] GLint GetEBOID(size_t idx) const;
    [[nodiscard]] GLint GetIndexBufferID() const;

    [[nodiscard]] GLboolean DoIndexing() const;

private:
    std::vector<glm::vec3>    vertexBuffer;
    std::vector<GLuint>       vertexIndices;
    std::vector<glm::vec2>    vertexUVs;
    std::vector<glm::vec3>    vertexNormals, vertexNormalDisplay;

    glm::vec3               boundingBox[2];
    GLfloat                 normalLength;

    DrawType                drawType = DrawType::TRIANGLE_STRIP;
    GLboolean               doIndexing = false;

    //todo might needed to another place?
    GLint mVAO_ID;
    GLint mIdxBufferID;
    std::vector<GLuint> mEBO_IDs;
};


#endif //SIMPLE_OBJ_SCENE_MESH_H
