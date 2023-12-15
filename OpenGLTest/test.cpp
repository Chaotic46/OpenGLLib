#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"

TEST(OpenGLWindowTests, GLWindowSizeTests)
{
	GLWindow window1;
	GLWindow window2(200, 200, "Window2 Title");

	EXPECT_EQ(window1.GetHeight(), 0);
	EXPECT_EQ(window1.GetWidth(), 0);
	EXPECT_EQ(window1.GetTitle(), std::string());

	EXPECT_EQ(window2.GetHeight(), 200);
	EXPECT_EQ(window2.GetWidth(), 200);
	EXPECT_EQ(window2.GetTitle(), std::string("Window2 Title"));

	window1.SetHeight(100);
	window1.SetWidth(100);
	window1.SetTitle("Title");

	EXPECT_EQ(window1.GetHeight(), 100);
	EXPECT_EQ(window1.GetWidth(), 100);
	EXPECT_EQ(window1.GetTitle(), std::string("Title"));
}