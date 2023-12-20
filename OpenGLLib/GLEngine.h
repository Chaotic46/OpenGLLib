#ifndef OPENGLENGINE_H_
#define OPENGLENGINE_H_

#include "GLWindow.h"

class GLEngine
{
public:
	static GLEngine* GetInstance();

	void PushGLWindow(GLWindow * window);
	GLWindow* PopGLWindow(unsigned int index);

	GLWindow* operator[](unsigned int index);

private:
	GLEngine();
	~GLEngine();
};

#endif