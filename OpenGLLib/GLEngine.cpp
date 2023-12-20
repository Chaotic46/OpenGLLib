#include "GLEngine.h"

GLEngine::GLEngine() : _renderingThread(this)
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

bool GLEngine::StartThread()
{
	return false;
}

bool GLEngine::StopThread()
{
	return false;
}

bool GLEngine::IsThreadRendering()
{
	return false;
}

// EngineRenderingThread methods
GLEngine::EngineRenderingThread::EngineRenderingThread(GLEngine* engine) : _engine(engine)
{}

bool GLEngine::EngineRenderingThread::IsThreadRendering()
{
	return true;
}

void GLEngine::EngineRenderingThread::RenderThread(EngineRenderingThread* renderThread)
{}