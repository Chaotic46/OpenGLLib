#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <string>

#include "GLCommon.h"

#include "GLFW/glfw3.h"

class GLWindow
{
public:
	GLWindow();
	GLWindow(unsigned int width, unsigned int height, std::string title, unsigned int major = 3, unsigned int minor = 3);
	~GLWindow();

	GLSize       GetSize()    const;
	unsigned int GetWidth()   const;
	unsigned int GetHeight()  const;
	std::string  GetTitle()   const;
	unsigned int GetGLMajor() const;
	unsigned int GetGLMinor() const;

	void SetSize(GLSize size);
	void SetWidth(unsigned int width);
	void SetHeight(unsigned int width);
	void SetTitle(std::string title);

private:
	void SetMajor(unsigned int major);
	void SetMinor(unsigned int minor);
	void CheckVersion(unsigned int & major, unsigned int & minor);
	void CheckSize(unsigned int & width, unsigned int & height);

	GLFWwindow * _window;

	unsigned int _width;
	unsigned int _height;
	std::string  _title;
};

#endif