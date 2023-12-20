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
	
}

GLWindow* GLEngine::PopGLWindow(unsigned int index)
{
	return NULL;
}

GLWindow* GLEngine::operator[](unsigned int inex)
{
	return NULL;
}