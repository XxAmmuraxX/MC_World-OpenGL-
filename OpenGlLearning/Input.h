#pragma once
#include <GLFW/glfw3.h>

class Input
{
    static GLFWwindow* window;

public:
    inline static void Init(GLFWwindow* _window) { window = _window; }

    static bool isKeyPressed(int key)
    {
        if (window && glfwGetKey(window, key) == GLFW_PRESS)
               return true;
        return false;
    }
};
