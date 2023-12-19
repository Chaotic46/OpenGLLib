#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"

void KeyCallbackTest(GLFWwindow* window, int key, int scancode, int action, int mods) {}
void CharCallbackTest(GLFWwindow* window, unsigned int codepoint)                     {}
void CharModsCallbackTest(GLFWwindow* window, unsigned int codepoint, int mods)       {}
void CursorPosCallbackTest(GLFWwindow* window, double xpos, double ypos)              {}
void CursorEnterCallbackTest(GLFWwindow* window, int entered)                         {}
void MouseButtonCallbackTest(GLFWwindow* window, int button, int action, int mods)    {}
void ScrollCallbackTest(GLFWwindow* window, double xoffset, double yoffset)           {}
void JoystickCallbackTest(int jid, int event)                                         {}
void DropCallbackTest(GLFWwindow* window, int path_count, const char* paths[])        {}

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

TEST(OpenGLWindowTests, GLCallbackTest)
{
	GLWindow window(GLSize(200, 200), " ");

	EXPECT_TRUE(window.SetKeyCallback(KeyCallbackTest) == NULL);
	EXPECT_TRUE(window.SetKeyCallback(NULL) == KeyCallbackTest);

	EXPECT_TRUE(window.SetCharCallback(CharCallbackTest) == NULL);
	EXPECT_TRUE(window.SetCharCallback(NULL) == CharCallbackTest);

	EXPECT_TRUE(window.SetCharModsCallback(CharModsCallbackTest) == NULL);
	EXPECT_TRUE(window.SetCharModsCallback(NULL) == CharModsCallbackTest);

	EXPECT_TRUE(window.SetCursorPosCallback(CursorPosCallbackTest) == NULL);
	EXPECT_TRUE(window.SetCursorPosCallback(NULL) == CursorPosCallbackTest);

	EXPECT_TRUE(window.SetCursorEnterCallback(CursorEnterCallbackTest) == NULL);
	EXPECT_TRUE(window.SetCursorEnterCallback(NULL) == CursorEnterCallbackTest);

	EXPECT_TRUE(window.SetMouseButtonCallback(MouseButtonCallbackTest) == NULL);
	EXPECT_TRUE(window.SetMouseButtonCallback(NULL) == MouseButtonCallbackTest);

	EXPECT_TRUE(window.SetScrollCallback(ScrollCallbackTest) == NULL);
	EXPECT_TRUE(window.SetScrollCallback(NULL) == ScrollCallbackTest);

	EXPECT_TRUE(window.SetJoystickCallback(JoystickCallbackTest) == NULL);
	EXPECT_TRUE(window.SetJoystickCallback(NULL) == JoystickCallbackTest);

	EXPECT_TRUE(window.SetDropCallback(DropCallbackTest) == NULL);
	EXPECT_TRUE(window.SetDropCallback(NULL) == DropCallbackTest);
}