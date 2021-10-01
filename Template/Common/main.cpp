//
// Created by yoonki on 9/10/21.
//
#include <Engine.h>
#include <iostream>
int main(){

    Engine::InitWindow(glm::vec2{2000, 1000}, "Test Title");
    Engine::InitEngine();

    do{
        Engine::Update();
        } while (Engine::IsRunning());
    Engine::CleanUp();
    return 0;
}