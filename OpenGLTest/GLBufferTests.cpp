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

	unsigned int bufferObject = 0;
	unsigned int vertexSize   = 0;
	unsigned int stride       = 0;
	unsigned int vertexType   = 0;
	unsigned int enabled      = 0;
	unsigned int normalized   = 0;

	buffer.BindVertexArray();

	buffer.AddBuffer(GL_ARRAY_BUFFER);

	buffer.AddAttribPointer(0, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	buffer.EnableAttribPointer(0, 0);

	glGetVertexAttribIuiv(0, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &bufferObject);
	glGetVertexAttribIuiv(0, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
	glGetVertexAttribIuiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &vertexSize);
	glGetVertexAttribIuiv(0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
	glGetVertexAttribIuiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &vertexType);
	glGetVertexAttribIuiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);

	EXPECT_EQ(bufferObject, buffer.GetBuffer(0));
	EXPECT_EQ(enabled, true);
	EXPECT_EQ(vertexSize, 3);
	EXPECT_EQ(stride, 3 * sizeof(float));
	EXPECT_EQ(vertexType, GL_FLOAT);
	EXPECT_EQ(normalized, false);
}