#include "GLEngine.h"

GLEngine::GLEngine()
{
	
}

GLEngine::~GLEngine()
{
	
}

GLEngine* GLEngine::GetInstance()
{
	static GLEngine engine;
	return &engine;
}

void GLEngine::PushGLWindow(GLWindow* window)
{
	_windowVector.push_back(window);
}

GLWindow* GLEngine::PopGLWindow(unsigned int index)
{
	GLWindow* window = _windowVector.at(index);

	_windowVector.erase(_windowVector.begin() + index);

	return window;
}

GLWindow* GLEngine::operator[](unsigned int index)
{
	return _windowVector.at(index);
}