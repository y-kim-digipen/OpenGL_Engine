a. How to use parts of your user interface that is NOT specified in the assignment description.
    - GUIManager
        - Wrapper class can easily add window/content
    - SceneBase
        - Base class of every scene 
        - Easy to add Object
            - Shader and meshs are already delivered with engine(todo to make it easy to User can add shader/mesh on engine)
            - Engine::GetVAO/VBOManager::AddObject(string objectName, string meshName, string shaderName)
    - Shader
        - Shader has it's own buffer for each object which use that shader, so automatially detected uniform variable is adjustable with GUI
b. Any assumption that you make on how to use the application that, if violated, might cause the application to fail.
c. Which part of the assignment has been completed?
    - All parts I think...
d. Which part of the assignment has NOT been completed (not done, not working, etc.) and
explanation on why those parts are not completed?
e. Where the relevant source codes (both C++ and shaders) for the assignment are located.
Specify the file path (folder name), file name, function name (or line number).
    - C++
        - "../Template/Common/*.cpp"
        - "../Template/Common/*.h"
    - shaders
        - "../Template/Common/Shaders/*.vert"
        - "../Template/Common/Shaders/*.frag"
    - meshes
        - "../Template/Common/models/*.obj"
f. Which machine did you test your application on.
    - my own laptop
        - "Ubuntu 20.04.3 LTS
        - GTX 1660ti
        - OpenGL 4.6.0 supported
    - Did not found any other roommate machine has linux machine.. so I can not test on other machine...
g. The number of hours you spent on the assignment, on a weekly basis
    - Week 1
        - 15
    - Week 2
        - 15
    - Week 3
        - 10
    - Week 4
        - 10
    - Week 5
        - 15
h. Any other useful information pertaining to the application