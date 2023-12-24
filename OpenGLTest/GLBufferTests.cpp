#include "gtest/gtest.h"

#include "../OpenGLLib/GLBuffer.h"

TEST(OpenGLBufferTests, GLBufferTest)
{
	GLBuffer buffer;

	buffer.BindVertexArray();

	EXPECT_TRUE(buffer.IsVertexArrayBound());

	buffer.AddBuffer(GL_ARRAY_BUFFER);
	buffer.AddBuffer(GL_ARRAY_BUFFER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	buffer.BindBuffer(0);

	EXPECT_FALSE(buffer.IsBufferBound(1));
	EXPECT_TRUE(buffer.IsBufferBound(0));

	buffer.BindBuffer(1);

	EXPECT_FALSE(buffer.IsBufferBound(0));
	EXPECT_TRUE(buffer.IsBufferBound(1));
}