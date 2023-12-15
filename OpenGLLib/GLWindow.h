#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <string>

#include "GLFW/glfw3.h"

class GLWindow
{
public:
	GLWindow();
	GLWindow(unsigned int width, unsigned int height, std::string title);
	~GLWindow();

	unsigned int GetWidth()  const;
	unsigned int GetHeight() const;
	std::string  GetTitle()  const;

	void SetWidth(unsigned int width);
	void SetHeight(unsigned int width);
	void SetTitle(std::string title);

private:
	GLFWwindow * _window;

	unsigned int _width;
	unsigned int _height;
	std::string  _title;
};

#endif