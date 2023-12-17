#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"

TEST(OpenGLWindowTests, GLWindowSizeTest)
{
	GLWindow window1;
	GLWindow window2(200, 200, "Window2 Title");

	EXPECT_EQ(window1.GetSize(),  GLSize(1, 1));
	EXPECT_EQ(window1.GetTitle(), std::string());

	EXPECT_EQ(window2.GetSize(), GLSize(200, 200));
	EXPECT_EQ(window2.GetTitle(), std::string("Window2 Title"));

	window1.SetSize(GLSize(100, 100));
	window1.SetTitle("Title");

	EXPECT_EQ(window1.GetSize(), GLSize(100, 100));
	EXPECT_EQ(window1.GetTitle(), std::string("Title"));
}

TEST(OpenGLWindowTests, GLVersionTest)
{
	GLWindow window(100, 100, "title", 3, 3);

	EXPECT_EQ(window.GetGLMajor(), 3);
	EXPECT_EQ(window.GetGLMinor(), 3);
}