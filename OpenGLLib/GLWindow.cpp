#include "GLWindow.h"

GLWindow::GLWindow() : _window(NULL),
                       _width(0),
                       _height(0),
                       _title(),
                       _major(1),
                       _minor(0)
{
	
}

GLWindow::GLWindow(unsigned int width, unsigned int height, std::string title, unsigned int major, unsigned int minor) : _window(NULL),
                                                                                                                         _width(width),
                                                                                                                         _height(height),
                                                                                                                         _title(title),
                                                                                                                         _major(major),
                                                                                                                         _minor(minor)
{
	
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
    return _major;
}

unsigned int GLWindow::GetGLMinor() const
{
    return _minor;
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
    
}

void GLWindow::SetMinor(unsigned int minor)
{

}