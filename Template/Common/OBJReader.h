/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: OBJReader.h
Purpose: Header file of OBJReader
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Pushpak Karnick, Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef SIMPLE_SCENE_OBJREADER_H
#define SIMPLE_SCENE_OBJREADER_H

#include <string>
#include <fstream>
#include <vector>

// for OpenGL datatypes
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Mesh.h"

class OBJReader
{

public:
    OBJReader();
    virtual ~OBJReader();

    // initialize the data
    void initData();


    // Read data from a file
    enum ReadMethod { LINE_BY_LINE, BLOCK_IO };
    double ReadOBJFile(std::string filepath,
                       Mesh *pMesh,
                       ReadMethod r = ReadMethod::LINE_BY_LINE,
                       GLboolean bFlipNormals = false);

private:

    // Read OBJ file line by line
    int ReadOBJFile_LineByLine( std::string filepath );

    // Read the OBJ file in blocks -- works for files smaller than 1GB
    int ReadOBJFile_BlockIO( std::string filepath );

    // Parse individual OBJ record (one line delimited by '\n')
    void ParseOBJRecord( char *buffer, glm::vec3 &min, glm::vec3 &max );

    // data members
    Mesh *      _currentMesh;
};


#endif //SIMPLE_SCENE_OBJREADER_H
