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

	bool StartThread();
	bool StopThread();
	bool IsThreadRendering();

private:
	GLEngine();
	~GLEngine();

	std::vector<GLWindow*> _windowVector;

	// Embedded thread class to handle rendering all the windows in GLEngine
	class EngineRenderingThread
	{
	public:
		EngineRenderingThread(GLEngine* engine);

		static void RenderThread(EngineRenderingThread* renderThread);
		bool        IsThreadRendering();

	private:
		GLEngine * _engine;
		bool       _renderAgain;
	};

	EngineRenderingThread _renderingThread;
};

#endif