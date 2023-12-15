#include "GLWindow.h"

GLWindow::GLWindow() : _window(NULL),
                       _width(1),
                       _height(1),
                       _title()
{

}

GLWindow::GLWindow(unsigned int width, unsigned int height, std::string title, unsigned int major, unsigned int minor) : _window(NULL),
                                                                                                                         _width(width),
                                                                                                                         _height(height),
                                                                                                                         _title(title)
{
    glfwInit();

    CheckVersion(major, minor);
    CheckSize(width, height);

    SetMajor(major);
    SetMinor(minor);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(_window);
}

GLWindow::~GLWindow()
{
	
}

unsigned int GLWindow::GetHeight() const
{
    return _height;
}

unsigned int GLWindow::GetWidth() const
{
    return _width;
}

std::string GLWindow::GetTitle() const
{
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

void GLWindow::SetWidth(unsigned int width)
{
    _width = width;
}

void GLWindow::SetHeight(unsigned int height)
{
    _height = height;
}

void GLWindow::SetTitle(std::string title)
{
    _title = title;
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

void GLWindow::CheckSize(unsigned int & width, unsigned int & height)
{
    if (width == 0)
    {
        width = 1;
    }

    if (height == 0)
    {
        height = 1;
    }
}