#include "gtest/gtest.h"

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

TEST(OpenGLShaderTest, GLShaderTest)
{
	GLShader shaderProgram;

	ASSERT_TRUE(shaderProgram.CreateVertex(vertexShader));
	ASSERT_TRUE(shaderProgram.CreateFragment(fragmentShader));

	EXPECT_TRUE(shaderProgram.LinkProgram());
}