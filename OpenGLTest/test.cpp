#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"

TEST(OpenGLRGBATest, GLRGBATest)
{
	GLRGBA rgba;

	EXPECT_EQ(rgba.GetR(), 0.0f);
	EXPECT_EQ(rgba.GetG(), 0.0f);
	EXPECT_EQ(rgba.GetB(), 0.0f);
	EXPECT_EQ(rgba.GetA(), 0.0f);

	rgba.SetR(0.5f);
	rgba.SetG(0.4f);
	rgba.SetB(0.6f);
	rgba.SetA(1.5f);

	EXPECT_EQ(rgba.GetR(), 0.5f);
	EXPECT_EQ(rgba.GetG(), 0.4f);
	EXPECT_EQ(rgba.GetB(), 0.6f);
	EXPECT_EQ(rgba.GetA(), 1.0f);
}

TEST(OpenGLWindowTests, GLWindowSizeTest)
{
	GLWindow window1;
	GLWindow window2(GLSize(200, 200), "Window2 Title");

	EXPECT_EQ(window1.GetSize(),  GLSize(0, 0));
	EXPECT_EQ(window1.GetTitle(), std::string());

	EXPECT_EQ(window2.GetSize(), GLSize(200, 200));
	EXPECT_EQ(window2.GetTitle(), std::string("Window2 Title"));

	window1.SetSize(GLSize(100, 100));
	window1.SetTitle("Title");

	EXPECT_EQ(window1.GetSize(), GLSize(0, 0));
	EXPECT_EQ(window1.GetTitle(), std::string());

	window2.SetSize(GLSize(100, 100));
	window2.SetTitle("Title");

	EXPECT_EQ(window2.GetSize(), GLSize(100, 100));
	EXPECT_EQ(window2.GetTitle(), std::string("Title"));
}

TEST(OpenGLWindowTests, GLVersionTest)
{
	GLWindow window(GLSize(100, 100), "title", 3, 3);

	EXPECT_EQ(window.GetGLMajor(), 3);
	EXPECT_EQ(window.GetGLMinor(), 3);
}

TEST(OpenGLWindowTests, GLBackgroundColourTest)
{
	GLWindow window1;
	GLRGBA backgroundColour(1.0f, 0.0f, 0.5f, 1.0f);

	EXPECT_EQ(window1.GetBackgroundColour(), GLRGBA());

	window1.SetBackgroundColour(backgroundColour);

	EXPECT_EQ(window1.GetBackgroundColour(), backgroundColour);
}

