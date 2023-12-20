#ifndef OPENGLENGINE_H_
#define OPENGLENGINE_H_

#include "GLWindow.h"

#include <vector>
#include <thread>
#include <future>
#include <chrono>

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
		~EngineRenderingThread();

		bool StartRendering();
		bool StopRendering();
		bool IsThreadRendering();

		static void RenderThread(EngineRenderingThread* renderThread);

	private:
		GLEngine * _engine;
		bool       _renderAgain;

		std::thread*                                      _renderingThreadHandle;
		std::future<void>                                 _threadStatus;
		std::packaged_task<void(EngineRenderingThread*)>* _threadTask;
	};

	EngineRenderingThread                             _renderingThread;
};

#endif