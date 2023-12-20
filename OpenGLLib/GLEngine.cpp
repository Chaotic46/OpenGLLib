#include "GLEngine.h"

using namespace std::chrono_literals;

GLEngine::GLEngine() : _renderingThread(this)
{
	
}

GLEngine::~GLEngine()
{
	// Make sure the thread is stopped
	if (IsThreadRendering())
	{
		StopThread();
	}

	// Clean up all the windows
	while (_windowVector.size() > 0)
	{
		GLWindow* window = PopGLWindow(0);
		delete window;
	}
}

GLEngine* GLEngine::GetInstance()
{
	static GLEngine engine;
	return &engine;
}

bool GLEngine::PushGLWindow(GLWindow* window)
{
	if (!window->IsInitialized())
	{
		return false;
	}

	_windowVector.push_back(window);

	return true;
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

/* \brief starts the thread by creating a new thread object using the GLEngine::EngineRenderingThread::RenderThread method.
 */
bool GLEngine::StartThread()
{
	return _renderingThread.StartRendering();
}

bool GLEngine::StopThread()
{
	return _renderingThread.StopRendering();
}

bool GLEngine::IsThreadRendering()
{
	return _renderingThread.IsThreadRendering();
}

// EngineRenderingThread methods
GLEngine::EngineRenderingThread::EngineRenderingThread(GLEngine* engine) : _engine(engine),
                                                                           _threadTask(NULL),
                                                                           _renderingThreadHandle(NULL),
                                                                           _renderAgain(false)
{}

GLEngine::EngineRenderingThread::~EngineRenderingThread()
{
	if (_threadTask)
	{
		delete _threadTask;
		delete _renderingThreadHandle;
	}
}

bool GLEngine::EngineRenderingThread::StartRendering()
{
	if (_threadTask)
	{
		// Thread is still running (hasnt been told to stop!)
		if (_threadStatus.wait_for(0ms) != std::future_status::ready)
		{
			return false;
		}

		delete _threadTask;
		delete _renderingThreadHandle;
	}

	_renderAgain = true;

	_threadTask            = new std::packaged_task<void(EngineRenderingThread*)>(GLEngine::EngineRenderingThread::RenderThread);
	_threadStatus          = _threadTask->get_future();
	_renderingThreadHandle = new std::thread(std::move(*_threadTask), this);

	return _threadStatus.wait_for(0ms) != std::future_status::ready;
}

bool GLEngine::EngineRenderingThread::StopRendering()
{
	// If the thread already stopped, no reason to go through any steps past this
	if (!IsThreadRendering())
	{
		return false;
	}

	_renderAgain = false;

	_renderingThreadHandle->join();

	return _threadStatus.wait_for(0ms) == std::future_status::ready;
}

bool GLEngine::EngineRenderingThread::IsThreadRendering()
{
	return _threadStatus.wait_for(0ms) != std::future_status::ready;
}

void GLEngine::EngineRenderingThread::RenderThread(EngineRenderingThread* renderThread)
{
	while (renderThread->_renderAgain)
	{
		for (unsigned int i = 0; i < renderThread->_engine->_windowVector.size(); i++)
		{
			GLWindow * window = renderThread->_engine->_windowVector[i];
			
			window->SetCurrentContext();

			window->ClearBackground();

			glfwPollEvents();

			window->SwapBuffers();
		}
	}
}