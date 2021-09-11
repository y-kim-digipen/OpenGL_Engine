//
// Created by yoonki on 9/10/21.
//
#include <Engine.h>
int main(){
    Engine::InitEngine();
    Engine::InitWindow(glm::vec2{500, 500}, "Test Title");


    do{
        Engine::Update();
    } while (Engine::IsRunning());

    Engine::CleanUp();
    return 0;
}