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