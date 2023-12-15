#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <string>

#include "GLFW/glfw3.h"

class GLWindow
{
public:
	GLWindow();
	GLWindow(unsigned int width, unsigned int height, std::string title, unsigned int major = 1, unsigned int minor = 0);
	~GLWindow();

	unsigned int GetWidth()   const;
	unsigned int GetHeight()  const;
	std::string  GetTitle()   const;
	unsigned int GetGLMajor() const;
	unsigned int GetGLMinor() const;

	void SetWidth(unsigned int width);
	void SetHeight(unsigned int width);
	void SetTitle(std::string title);
	void SetMajor(unsigned int major);
	void SetMinor(unsigned int minor);

private:
	GLFWwindow * _window;

	unsigned int _width;
	unsigned int _height;
	std::string  _title;

	unsigned int _major;
	unsigned int _minor;
};

#endif