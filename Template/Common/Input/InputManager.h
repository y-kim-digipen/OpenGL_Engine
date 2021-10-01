/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: InputManager.h
Purpose: Header of InputManager
Language: c++, g++
Platform: linux_amd64, opengl 4.1 support gpu required
Project:y.kim_CS300_1
Author: Yoonki Kim, 180002421, y.kim
Creation date: 10/1/21
End Header --------------------------------------------------------*/
#ifndef ENGINE_INPUTMANAGER_H
#define ENGINE_INPUTMANAGER_H
#include <utility>
#include <array>
#include "KeyCodes.h"

class InputManager{
friend class Engine;
public:
    static void Init();
    static void Update();
    static void CleanUp();

    static bool IsPressed(GLint KeyCode);
    static bool IsReleased(GLint KeyCode);
    static bool OnKeyDown(GLint KeyCode);

private:
    //Implementation for GLFW callback from Engine
    static void on_key_pressed(GLint KeyCode);
    static void on_key_released(GLint KeyCode);
//    static void on_mouse_pressed(int button);
//    static void on_mouse_released(int button);
//    static void on_mouse_scrolled(double offset);

private:
    inline static std::array<bool, GLFW_KEY_LAST> mNewKeyBuffer, mOldKeyBuffer;
//    static bool IsAnyKeyPressed, IsAnyKeyReleased, IsAnyKeyDown;
};
#endif //ENGINE_INPUTMANAGER_H
