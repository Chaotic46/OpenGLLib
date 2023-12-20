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