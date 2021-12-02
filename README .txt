/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: README.txt
Purpose: Just a readme for assignment 3
Language: c++, gcc
Platform: Linux, opengl 4.5 support gpu required
Project: y.kim_CS300_3
Author: Yoonki Kim, 180002421, y.kim
Creation date: December 2, 2021
End Header --------------------------------------------------------*/
a. How to use parts of your user interface that is NOT specified in the assignment description.


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
    ////Important!!//////
    - I made Seperate tab for grading assignment, find ObjectList GUI -> Press 'CentralObject' Detail, and go to Assigment3_GUI Tab.. 
        there are GUI for grading assignment
        - You could select ReflectOnly/RefractOnly/Frensel + Phong
        - If you select Frensel + Phong.. you could modify mix Ratio(in other selection it will not shown)

    - Variable E to R, G, B are at the 'ShaderUniforms' Tab (EmissiveColor only work with Frensel + Phong mode)
        
    - Object/Light list Panel shows all the object/light in the current scene
        - Press detail to popup detail panel / press Collapse to close
            - There are multiple taps in the detail panel
                - Assets
                    - You can replace mesh / shader
                - Transforms
                - ShaderUniforms
                    - Automatically detected shader uniform variables are here, you could adjust it
                - Texture
                    - UV Calculate method selection
                    - Using Texture and Using GPU_UV option
                - Others
                    - Has normal drawing options...
            
            - Only for lights
                - Lightdata tab has all the variable required for assignemnt 2 (Type, Ka, Kd ....)
    - Global Setting 
        - FogColor, Globalambient
        - Add/Remove light
        - Select Scenario
        - Support Shader reloading

b. Any assumption that you make on how to use the application that, if violated, might cause the application to fail.
c. Which part of the assignment has been completed?
    - All parts I think...
d. Which part of the assignment has NOT been completed (not done, not working, etc.) and
explanation on why those parts are not completed?
    - All parts are completed
e. Where the relevant source codes (both C++ and shaders) for the assignment are located.
Specify the file path (folder name), file name, function name (or line number).
    - FBO
        - "../Template/Common/FBO.h & cpp
    - Reflecion / Refraction
        - "../Template/Shader/ReflectionShader.vert & frag"
        - "../Template/Shader/RefractionShader.vert & frag"
        - "../Template/Shader/FrenselPhong.vert & frag"

    - CubeMapping / Environment Mapping
        - "../Template/Common/CubeCapureCamera.h & cpp
        - "../Template/Common/CubeObject.h & cpp
        - "../Template/Shader/FSQ.vert & frag"


f. Which machine did you test your application on.
    - my own laptop
        - "Ubuntu 20.04.3 LTS
        - GTX 1660ti
        - OpenGL 4.6.0 supported
    - my second laptop
        - "Ubuntu 20.04.3 LTS
        - GTX 3050ti
        - OpenGL 4.6.0 supported
    - Did not found any other roommate machine has linux machine.. so I can not test on other machine...

g. The number of hours you spent on the assignment, on a weekly basis
    - 1st Week
        - 5
    - 2nd Week
        - 25
    - 3rd Week
        - 5
    - 4th Week
        - 5
        
h. Any other useful information pertaining to the application

Build Instruction
    Dependency
        glfw3r
        OpenGL
        GLEW
        IMGUI - Included with file
        Font  - What I'm using, it's also with the file
Use CMake as a build tool
        "$cd "../Template/Common/cmake-build-debug/"
        "$mkdir build"
        "$cd build"
        "$cmake .."
        "$make"
        "$./Engine" to run the program
Run with executable file
        go to Executable
      	"$./Engine"
Or you could open template folder with clion.. and Open CMakeList.txt! and build & run