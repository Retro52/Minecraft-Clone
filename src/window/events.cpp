//
// Created by Anton on 17.06.2021.
//

#include "events.h"

#include "../OpenGL/include/GLEW/glew.h"
#include "../OpenGL/include/GLFW/glfw3.h"
#include <cstring>

bool* Events::_keys;
uint* Events::_frames;
uint Events::_current = 0;
uint Events::_previous = 0;
double Events::deltaX = 0.0f;
double Events::deltaY = 0.0f;
double Events::x = 0.0f;
double Events::y = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

#define _MOUSE_BUTTONS 1024

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (Events::_cursor_started)
    {
        const double sensetivity = 1.0;
        Events::deltaX += (xpos-Events::x) / 3.0;
        Events::deltaY += (ypos-Events::y) / 3.0;
        Events::deltaX += sensetivity * (xpos-Events::x);
        Events::deltaY += sensetivity * (ypos-Events::y);
    }
    else
    {
        Events::_cursor_started = true;
    }
    Events::x = xpos;
    Events::y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
    if (action == GLFW_PRESS)
    {
        Events::_keys[_MOUSE_BUTTONS+button] = true;
        Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::_keys[_MOUSE_BUTTONS+button] = false;
        Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS)
    {
        Events::_keys[key] = true;
        Events::_frames[key] = Events::_current;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::_keys[key] = false;
        Events::_frames[key] = Events::_current;
    }
}

void window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}

int Events::initialize()
{
    GLFWwindow* window = Window::window;
    _keys = new bool[1032];
    _frames = new uint[1032];

    memset(_keys, false, 1032*sizeof(bool));
    memset(_frames, 0, 1032*sizeof(uint));

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    return 0;
}

bool Events::pressed(int keycode)
{
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
        return false;
    return _keys[keycode];
}

bool Events::jpressed(int keycode)
{
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
        return false;
    return _keys[keycode] && (_frames[keycode] == _current || _frames[keycode] == _previous);
}

bool Events::clicked(int button)
{
    int index = _MOUSE_BUTTONS+button;
    return _keys[index];
}

bool Events::jclicked(int button)
{
    int index = _MOUSE_BUTTONS+button;
    return _keys[index] && (_frames[index] == _current || _frames[index] == _previous);
}

void Events::pullEvents()
{
    _current++;
    _previous++;
    deltaX = 0.0f;
    deltaY = 0.0f;
    glfwPollEvents();
}

void Events::toogleCursor()
{
    _cursor_locked = !_cursor_locked;
    Window::setCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_HIDDEN);
}
