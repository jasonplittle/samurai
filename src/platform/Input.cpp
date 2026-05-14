#include "Input.hpp"

#include <iostream>


bool Input::IsKeyPressed(GLFWwindow *window, int keycode)
{
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 Input::GetCursorPos(GLFWwindow *window)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return glm::vec2(x, y);
}

bool Input::IsMousePressed(GLFWwindow *window, int keycode)
{
    auto state = glfwGetMouseButton(window, keycode);
    return state == GLFW_PRESS;
}
