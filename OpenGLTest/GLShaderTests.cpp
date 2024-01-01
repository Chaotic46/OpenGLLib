#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"
#include "../OpenGLLib/GLBuffer.h"

#include "../OpenGLLib/GLShader.h"

// Sample shader programs

// Vertex shader obtained from learnopengl.com
const char* vertexShader =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
""
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

// Fragment shader obtained from learnopengl.com
const char* fragmentShader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

// Geometry shader obtained from learnopengl.com
const char* geometryShader =
"#version 330 core\n"
"layout(points) in;\n"
"layout(line_strip, max_vertices = 2) out;\n"
"\n"
"void main() {\n"
"    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);\n"
"    EmitVertex();\n"
"\n"
"    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);\n"
"    EmitVertex();\n"
"\n"
"    EndPrimitive();\n"
"}\n";

TEST(OpenGLShaderTest, GLShaderTest)
{
	GLShader shaderProgram;

	ASSERT_TRUE(shaderProgram.CreateVertex(vertexShader));
	ASSERT_TRUE(shaderProgram.CreateFragment(fragmentShader));

	EXPECT_TRUE(shaderProgram.LinkProgram());

	ASSERT_TRUE(shaderProgram.CreateGeometry(geometryShader));

	EXPECT_TRUE(shaderProgram.LinkProgram());
}

TEST(OpenGLShaderTest, GLUseShaderProgramTest)
{
	GLShader shaderProgram;

	// We haven't linked our shader program, thus it hasn't been created
	shaderProgram.UseProgram();
	EXPECT_FALSE(shaderProgram.IsProgramUsed());

	// Link our shader program so it can be used.
	EXPECT_TRUE(shaderProgram.CreateVertex(vertexShader));
	EXPECT_TRUE(shaderProgram.CreateFragment(fragmentShader));
	EXPECT_TRUE(shaderProgram.LinkProgram());

	shaderProgram.UseProgram();
	EXPECT_TRUE(shaderProgram.IsProgramUsed());
}

TEST(OpenGLShaderTest, GLAttachBufferToShaderTest)
{
	GLWindow window(GLSize(200, 200), " ");
	GLShader* shader  = new GLShader;
	GLBuffer* buffer1 = new GLBuffer;
	GLBuffer* buffer2 = new GLBuffer;

	EXPECT_EQ(shader->GetAttachedBuffer(), (GLBuffer*)NULL);

	shader->AttachBuffer(buffer1);

	EXPECT_EQ(shader->GetAttachedBuffer(), buffer1);

	shader->AttachBuffer(buffer2);

	EXPECT_NE(shader->GetAttachedBuffer(), buffer1);
	EXPECT_EQ(shader->GetAttachedBuffer(), buffer2);
}