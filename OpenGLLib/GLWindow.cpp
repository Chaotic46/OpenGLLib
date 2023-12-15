#include "GLWindow.h"

GLWindow::GLWindow() : _window(NULL),
                       _width(0),
                       _height(0),
                       _title()
{
	
}

GLWindow::GLWindow(unsigned int width, unsigned int height, std::string title) : _window(NULL),
                                                                                 _width(width),
                                                                                 _height(height),
                                                                                 _title(title)
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