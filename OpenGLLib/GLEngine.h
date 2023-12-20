#ifndef OPENGLENGINE_H_
#define OPENGLENGINE_H_

#include "GLWindow.h"

#include <vector>

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

	std::vector<GLWindow*> _windowVector;
};

#endif