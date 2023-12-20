#include "gtest/gtest.h"

#include "../OpenGLLib/GLEngine.h"

TEST(OpenGLEngineTests, OpenGLEngineInstanceTest)
{
	GLEngine* engine1 = GLEngine::GetInstance();
	GLEngine* engine2 = GLEngine::GetInstance();

	EXPECT_TRUE(engine1 != NULL);
	EXPECT_TRUE(engine2 != NULL);
	EXPECT_TRUE(engine1 == engine2);
}

TEST(OpenGLEngineTests, OpenGLEngineAddWindowTest)
{
	GLWindow* window1 = new GLWindow();
	GLWindow* window2 = new GLWindow();
	GLWindow* window3 = new GLWindow();

	GLEngine* engine = GLEngine::GetInstance();

	engine->PushGLWindow(window1);
	engine->PushGLWindow(window2);
	engine->PushGLWindow(window3);

	EXPECT_EQ((*engine)[0], window1);
	EXPECT_EQ((*engine)[1], window2);
	EXPECT_EQ((*engine)[2], window3);
	EXPECT_THROW((*engine)[3], std::out_of_range); // Catch an out of bounds exception

	EXPECT_EQ(engine->PopGLWindow(2), window3);
	EXPECT_EQ(engine->PopGLWindow(0), window1);
	EXPECT_EQ(engine->PopGLWindow(0), window2);
	EXPECT_THROW(engine->PopGLWindow(0), std::out_of_range);
}