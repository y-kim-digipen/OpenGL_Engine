/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: Main entry point
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project: y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#include <Engine.h>
#include <iostream>
int main(){

    Engine::InitWindow(glm::vec2{2000, 1000}, "Assignment 1");
    Engine::InitEngine();

    do{
        Engine::Update();
        } while (Engine::IsRunning());
    Engine::CleanUp();
    return 0;
}