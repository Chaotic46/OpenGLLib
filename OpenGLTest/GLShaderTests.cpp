#include "gtest/gtest.h"

#include "../OpenGLLib/GLWindow.h"
#include "../OpenGLLib/GLBuffer.h"

#include "../OpenGLLib/GLShader.h"

// Sample shader programs

// Vertex shader Using multiple uniforms
const char* vertexUniformShader =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
""
"uniform vec4 inFloat4;\n"
"uniform vec4 inFloat4V[2];\n"
"uniform mat4 inMat4;\n"
""
"void main()\n"
"{\n"
"	vec4 temp = inFloat4;\n"
""
"	for(int i = 0; i < 2; i++)\n"
"	{\n"
"		temp += inFloat4V[i];\n"
"	}\n"
""
"	temp = inMat4 * temp;\n"
""
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) + temp;\n"
"}\n";

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

template<class T>
bool CompareVals(T* in1, T* in2, int size)
{
	for (unsigned int i = 0; i < size; i++)
	{
		if (in1[i] != in2[i])
		{
			return false;
		}
	}

	return true;
}

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

	glUseProgram(0);
}

TEST(OpenGLShaderTest, GLModifyUniformsTest)
{
	GLShader     shaderProgram;
	const int    kNumValues = 16;
	float        inFloat[kNumValues];
	float        outFloat[kNumValues];

	EXPECT_TRUE(shaderProgram.CreateVertex(vertexUniformShader));
	EXPECT_TRUE(shaderProgram.CreateFragment(fragmentShader));
	EXPECT_TRUE(shaderProgram.LinkProgram());

	// Use the linked program so the uniforms are enabled
	shaderProgram.UseProgram();
	EXPECT_TRUE(shaderProgram.IsProgramUsed());

	// Setup test values
	for (int i = 0; i < kNumValues; i++)
	{
		inFloat[i] = i + 0.5f;
	}

	memset(outFloat, 0, kNumValues * sizeof(float));

	ASSERT_TRUE(shaderProgram.SetUniform("inFloat4", inFloat,  GL_UNIFORM_FLOAT4, 1));
	ASSERT_TRUE(shaderProgram.GetUniform("inFloat4", outFloat, GL_UNIFORM_FLOAT4));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 4));

	memset(outFloat, 0, kNumValues * sizeof(float));

	ASSERT_TRUE(shaderProgram.SetUniform("inFloat4V", inFloat,  GL_UNIFORM_FLOAT4, 2));
	ASSERT_TRUE(shaderProgram.GetUniform("inFloat4V[0]", outFloat, GL_UNIFORM_FLOAT4));
	ASSERT_TRUE(shaderProgram.GetUniform("inFloat4V[1]", &outFloat[4], GL_UNIFORM_FLOAT4));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 8));

	memset(outFloat, 0, kNumValues * sizeof(float));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat4", inFloat,  GL_UNIFORM_MAT4, 1));
	ASSERT_TRUE(shaderProgram.GetUniform("inMat4", outFloat, GL_UNIFORM_MAT4));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 16));
}