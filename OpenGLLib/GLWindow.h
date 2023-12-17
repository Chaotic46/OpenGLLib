#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <string>

#include "GLCommon.h"

#include "GLFW/glfw3.h"

class GLWindow
{
public:
	GLWindow();
	GLWindow(GLSize size, std::string title, unsigned int major = 3, unsigned int minor = 3);
	~GLWindow();

	GLSize       GetSize()    const;
	std::string  GetTitle()   const;
	unsigned int GetGLMajor() const;
	unsigned int GetGLMinor() const;

	void SetSize(GLSize size);
	void SetTitle(std::string title);

private:
	void SetMajor(unsigned int major);
	void SetMinor(unsigned int minor);
	void CheckVersion(unsigned int & major, unsigned int & minor);
	void CheckSize(GLSize size);

	GLFWwindow * _window;
	std::string  _title;
};

#endif