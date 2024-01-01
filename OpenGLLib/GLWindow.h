#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <string>

#include "GLCommon.h"
#include "GLShader.h"

class GLWindow
{
public:
	GLWindow();
	GLWindow(GLSize size, std::string title, unsigned int major = 3, unsigned int minor = 3, unsigned int hints = 0);
	~GLWindow();

	bool Create(GLSize size, std::string title, unsigned int major = 3, unsigned int minor = 3, unsigned int hints = 0);

	bool IsInitialized();

	GLSize       GetSize()             const;
	std::string  GetTitle()            const;
	unsigned int GetGLMajor()          const;
	unsigned int GetGLMinor()          const;
	GLRGBA       GetBackgroundColour() const;
	GLShader   * GetAttachedShader()   const;

	void SetCurrentContext();
	void SetSize(GLSize size);
	void SetTitle(std::string title);
	void SetBackgroundColour(GLRGBA backgroundColour);
	void AttachShader(GLShader * shader);

	void ClearBackground();
	void SwapBuffers();

	bool IsWindowResizable();
	bool IsWindowDecorated();
	bool IsWindowMaximized();
	bool IsWindowMinimized();
	bool IsWindowVisible();
	bool IsWindowAutoMinimized();
	bool IsWindowFloating();
	bool IsWindowFocusedOnShow();
	bool IsWindowFocused();

	void SetWindowResizable(bool resizable = true);
	void SetWindowDecorated(bool decorate = true);
	void SetWindowAutoMinimize(bool autoIconify = true);
	void SetFocusOnShow(bool focus = true);

	void Show();
	void Hide();
	void Focus(bool focus = true);
	void Maximize(bool maximize = true);
	void Minimize(bool minimize = true);
	void Float(bool windowFloat = true);

	// Callbacks to user inputs
	GLFWkeyfun         SetKeyCallback(GLFWkeyfun callback);
	GLFWcharfun        SetCharCallback(GLFWcharfun callback);
	GLFWcharmodsfun    SetCharModsCallback(GLFWcharmodsfun callback);
	GLFWcursorposfun   SetCursorPosCallback(GLFWcursorposfun callback);
	GLFWcursorenterfun SetCursorEnterCallback(GLFWcursorenterfun callback);
	GLFWmousebuttonfun SetMouseButtonCallback(GLFWmousebuttonfun callback);
	GLFWscrollfun      SetScrollCallback(GLFWscrollfun callback);
	GLFWjoystickfun    SetJoystickCallback(GLFWjoystickfun callback);
	GLFWdropfun        SetDropCallback(GLFWdropfun callback);

	// Callbacks to modifications to the window
	GLFWwindowposfun          SetWindowPosCallback(GLFWwindowposfun callback);
	GLFWwindowsizefun         SetWindowSizeCallback(GLFWwindowsizefun callback);
	GLFWwindowclosefun        SetWindowCloseCallback(GLFWwindowclosefun callback);
	GLFWwindowrefreshfun      SetWindowRefreshCallback(GLFWwindowrefreshfun callback);
	GLFWwindowfocusfun        SetWindowFocusCallback(GLFWwindowfocusfun callback);
	GLFWwindowiconifyfun      SetWindowIconifyCallback(GLFWwindowiconifyfun callback);
	GLFWwindowmaximizefun     SetWindowMaximizeCallback(GLFWwindowmaximizefun callback);
	GLFWframebuffersizefun    SetFramebufferSizeCallback(GLFWframebuffersizefun callback);
	GLFWwindowcontentscalefun SetWindowContentScaleCallback(GLFWwindowcontentscalefun callback);

	// Callbacks related to monitors
	GLFWmonitorfun SetMonitorCallback(GLFWmonitorfun callback);

private:
	void SetMajor(unsigned int major);
	void SetMinor(unsigned int minor);
	void CheckVersion(unsigned int & major, unsigned int & minor);
	void CheckSize(GLSize size);

	GLFWwindow * _window;
	GLShader   * _shader;
	std::string  _title;
	GLRGBA       _backgroundColour;
	bool         _initialized;
};

#endif