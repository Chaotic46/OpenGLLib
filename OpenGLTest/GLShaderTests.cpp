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