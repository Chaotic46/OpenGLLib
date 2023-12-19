#include "glad/glad.h"
#include "GLWindow.h"

GLWindow::GLWindow() : _window(NULL)
{

}

GLWindow::GLWindow(GLSize size, std::string title, unsigned int major, unsigned int minor) : _window(NULL),
                                                                                             _title(title)
{
    glfwInit();

    CheckVersion(major, minor);
    CheckSize(size);

    SetMajor(major);
    SetMinor(minor);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    _window = glfwCreateWindow(size.first, size.second, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLWindow::~GLWindow()
{
    if (_window)
    {
        glfwDestroyWindow(_window);
    }
}


GLSize GLWindow::GetSize() const
{
    if (!_window)
    {
        return GLSize();
    }

    GLSize size;

    glfwGetWindowSize(_window, &size.first, &size.second);

    return size;
}

std::string GLWindow::GetTitle() const
{
    // There is no glfw method to obtain the window title, thus we have to use a variable to keep track of it.
    return _title;
}

unsigned int GLWindow::GetGLMajor() const
{
    int test = glfwGetWindowAttrib(_window, GLFW_CONTEXT_VERSION_MAJOR);
    return test;
}

unsigned int GLWindow::GetGLMinor() const
{
    return glfwGetWindowAttrib(_window, GLFW_CONTEXT_VERSION_MINOR);
}

GLRGBA GLWindow::GetBackgroundColour() const
{
    return _backgroundColour;
}

void GLWindow::SetSize(GLSize size)
{
    if (!_window)
    {
        return;
    }

    CheckSize(size);

    glfwSetWindowSize(_window, size.first, size.second);
}

void GLWindow::SetTitle(std::string title)
{
    if (!_window)
    {
        return;
    }

    glfwSetWindowTitle(_window, title.c_str());
    _title = title;
}

void GLWindow::SetBackgroundColour(GLRGBA backgroundColour)
{
    _backgroundColour = backgroundColour;
}

void GLWindow::Show()
{
    if (_window)
    {
        glfwShowWindow(_window);
    }
}

void GLWindow::Hide()
{
    if (_window)
    {
        glfwHideWindow(_window);
    }
}

GLFWkeyfun GLWindow::SetKeyCallback(GLFWkeyfun callback)
{
    return glfwSetKeyCallback(_window, callback);
}

GLFWcharfun GLWindow::SetCharCallback(GLFWcharfun callback)
{
    return glfwSetCharCallback(_window, callback);
}

GLFWcharmodsfun GLWindow::SetCharModsCallback(GLFWcharmodsfun callback)
{
    return glfwSetCharModsCallback(_window, callback);
}

GLFWcursorposfun GLWindow::SetCursorPosCallback(GLFWcursorposfun callback)
{
    return glfwSetCursorPosCallback(_window, callback);
}

GLFWcursorenterfun GLWindow::SetCursorEnterCallback(GLFWcursorenterfun callback)
{
    return glfwSetCursorEnterCallback(_window, callback);
}

GLFWmousebuttonfun GLWindow::SetMouseButtonCallback(GLFWmousebuttonfun callback)
{
    return glfwSetMouseButtonCallback(_window, callback);
}

GLFWscrollfun GLWindow::SetScrollCallback(GLFWscrollfun callback)
{
    return glfwSetScrollCallback(_window, callback);
}

GLFWjoystickfun GLWindow::SetJoystickCallback(GLFWjoystickfun callback)
{
    return glfwSetJoystickCallback(callback);
}

GLFWdropfun GLWindow::SetDropCallback(GLFWdropfun callback)
{
    return glfwSetDropCallback(_window, callback);
}

void GLWindow::SetMajor(unsigned int major)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
}

void GLWindow::SetMinor(unsigned int minor)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void GLWindow::CheckVersion(unsigned int & major, unsigned int & minor)
{
    switch(major)
    {
        case(1):
        {
            if (minor > 5)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        case(2):
        {
            if (minor > 1)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        case(3):
        {
            if (minor > 3)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        case(4):
        {
            if (minor > 6)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        default:
        {
            major = 1;
            minor = 0;
        }
    }
}

void GLWindow::CheckSize(GLSize size)
{
    if (size.first < 1)
    {
        size.first = 1;
    }

    if (size.second < 1)
    {
        size.second = 1;
    }
}