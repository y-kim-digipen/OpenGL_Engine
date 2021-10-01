# CS300 Assignment 1
## CopyRight

    Copyright (C) 2021 DigiPen Institute of Technology.
    Reproduction or disclosure of this file or its contents without the prior written
    consent of DigiPen Institute of Technology is prohibited.
------------
## About this file
>File Name: README.md <br />
>Purpose: Just a readme file <br />
>Language: Makrdown <br />
>Platform: g++, linux_amd64, opengl 4.1 support gpu required <br />
>Project: y.kim_CS300_1 <br />
>Author: Yoonki Kim, y.kim, 180002421 <br />
>Creation date: Oct 01, 2021 <br />
------------
## About Project
### Basic information
- Fall 2021, CS300 <br />
    - Assignment 1 <br />
### Description
For your first programming assignment, you are to implement a GUI-driven application
with the following requirements/features <br />
1. Scene Setup<br />
    - Central Object<br />
    - Spheres<br />
    - Orbit of the spheres<br />
2. Geometry Operations
    - Load obj file with reader<br />
        - 4sphere
        - bunny
        - cube
        - sphere_modified
    - Mesh with calculated per_vertex normal
    - Display face and vertex normals
    - Student own rendering method
    - menu-driven functionality
3. Lighting
    - Diffuse lighting (from directional light source)
    - Ambient lighting
------------
## Build Instruction
### With CLion
    "../Template/Common/CMakeLists.txt"
### Use CMake as a build tool
    "../Template/Common/cmake-build-debug/"
    Has all the files you need to build with cmake
------------
## Run with executable file
    //todo
    ""
------------
## Control instruction
- Camera move
    - W, A, S, ,D 
        - move camera's location, similar to FPS control
    - Space, Ctrl 
        - go up/down side
    - Q, E 
        - Roll
    - Arrow buttons 
        - Yaw / Pitch 

- GUI
    - Object list Panel shows all the object in the current scene
        - Press detail to popup detail panel / press Collapse to close
            - There are multiple taps in the detail panel
                - Assets
                    - You can replace mesh / shader
                - Transforms
                - ShaderUniforms
                    - Automatically detected shader uniform variables are here, you could adjust it
                - Others
                    - Has normal drawing options...
