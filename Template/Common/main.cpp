//
// Created by yoonki on 9/10/21.
//
#include <Engine.h>

int main(){

    Engine::InitWindow(glm::vec2{1600, 900}, "Assignment 2");
    Engine::InitEngine();

    do{
        Engine::Update();
        } while (Engine::IsRunning());
    Engine::CleanUp();
    return 0;
}