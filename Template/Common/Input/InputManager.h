//
// Created by yoonki on 9/10/21.
//
#ifndef ENGINE_INPUTMANAGER_H
#define ENGINE_INPUTMANAGER_H
#include <utility>
#include <vector>
#include "KeyCodes.h"
class InputManager{
friend class Engine;
public:
    static void Init();
    static void Update();
    static void CleanUp();

    static bool IsPressed(Key KeyCode);
    static bool IsReleased(Key KeyCode);
    static bool OnKeyDown(Key KeyCode);

private:
    //Implementation for GLFW callback from Engine
    static void on_key_pressed(Key KeyCode);
    static void on_key_released(Key KeyCode);
//    static void on_mouse_pressed(int button);
//    static void on_mouse_released(int button);
//    static void on_mouse_scrolled(double offset);

private:
    static std::vector<bool> mNewKeyBuffer, mOldKeyBuffer;
//    static bool IsAnyKeyPressed, IsAnyKeyReleased, IsAnyKeyDown;
};
#endif //ENGINE_INPUTMANAGER_H
