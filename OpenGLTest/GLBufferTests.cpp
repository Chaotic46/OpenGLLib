#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"
#include "../OpenGLLib/GLBuffer.h"

TEST(OpenGLBufferTests, GLBufferTest)
{
	// We need to create a window to have a valid context to load glad.
	GLWindow window(GLSize(100, 100), "title");
	GLBuffer buffer;

	buffer.BindVertexArray();

	EXPECT_TRUE(buffer.IsVertexArrayBound());

	EXPECT_THROW(buffer.BindBuffer(0), std::out_of_range);
	EXPECT_THROW(buffer.IsBufferBound(0), std::out_of_range);

	buffer.AddBuffer(GL_ARRAY_BUFFER);
	buffer.AddBuffer(GL_ARRAY_BUFFER);

	buffer.BindBuffer(0);

	EXPECT_FALSE(buffer.IsBufferBound(1));
	EXPECT_TRUE(buffer.IsBufferBound(0));

	buffer.BindBuffer(1);

	EXPECT_FALSE(buffer.IsBufferBound(0));
	EXPECT_TRUE(buffer.IsBufferBound(1));
}

TEST(OpenGLBufferTests, GLAttributePointerTest)
{
	// We need to create a window to have a valid context to load glad.
	GLWindow window(GLSize(100, 100), "title");
	GLBuffer buffer;

	buffer.BindVertexArray();

	buffer.AddBuffer(GL_ARRAY_BUFFER);

	buffer.ModifyAttribPointer(0, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}