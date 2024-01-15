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
"uniform float inFloat1;"
"uniform vec2  inFloat2;"
"uniform vec3  inFloat3;"
"uniform vec4  inFloat4;"
""
"uniform int   inInt1;"
"uniform ivec2 inInt2;"
"uniform ivec3 inInt3;"
"uniform ivec4 inInt4;"
""
"uniform uint  inUInt1;"
"uniform uvec2 inUInt2;"
"uniform uvec3 inUInt3;"
"uniform uvec4 inUInt4;"
""
"uniform float inFloat1V[2];"
"uniform vec2  inFloat2V[2];"
"uniform vec3  inFloat3V[2];"
"uniform vec4  inFloat4V[2];"
""
"uniform int   inInt1V[2];"
"uniform ivec2 inInt2V[2];"
"uniform ivec3 inInt3V[2];"
"uniform ivec4 inInt4V[2];"
""
"uniform uint  inUInt1V[2];"
"uniform uvec2 inUInt2V[2];"
"uniform uvec3 inUInt3V[2];"
"uniform uvec4 inUInt4V[2];"
""
"uniform mat2 inMat2V[2];"
"uniform mat3 inMat3V[2];"
"uniform mat4 inMat4V[2];"
""
"uniform mat2x3 inMat2x3V[2];"
"uniform mat3x2 inMat3x2V[2];"
"uniform mat4x2 inMat4x2V[2];"
"uniform mat2x4 inMat2x4V[2];"
"uniform mat4x3 inMat4x3V[2];"
"uniform mat3x4 inMat3x4V[2];"
""
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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

TEST(OpenGLShaderTest, GLModifyUniformsTest)
{
	GLShader     shaderProgram;

	const int    kNumValues = 32;

	unsigned int inUnsignedInt[kNumValues];
	int          inInt[kNumValues];
	float        inFloat[kNumValues];

	int          outInt[kNumValues];
	float        outFloat[kNumValues];
	unsigned int outUnsigned[kNumValues];

	int          sizeArray[] = {1, 2, 2, 4, 3, 6, 4, 8};

	EXPECT_TRUE(shaderProgram.CreateVertex(vertexUniformShader));
	EXPECT_TRUE(shaderProgram.CreateFragment(fragmentShader));
	EXPECT_TRUE(shaderProgram.LinkProgram());

	// Use the linked program so the uniforms are enabled
	shaderProgram.UseProgram();

	// Setup test values
	for (int i = 0; i < kNumValues; i++)
	{
		inUnsignedInt[i] = i + 1;
		inInt[i]         = -1 * (i + 1);
		inFloat[i]       = i + 0.5f;
	}

	// Test non-matrix uniforms
	for (unsigned int i = 0; i < 8; i++)
	{
		int  numLabel = (i / 2) + 1;
		bool isArray  = (i + 1) % 2 == 0;

		std::string intStr   = "inInt"   + std::to_string(numLabel) + (isArray ? "V" : "");
		std::string uintStr  = "inUInt"  + std::to_string(numLabel) + (isArray ? "V" : "");
		std::string floatStr = "inFloat" + std::to_string(numLabel) + (isArray ? "V" : "");

		
		ASSERT_TRUE(shaderProgram.SetUniform(intStr.c_str(),   inInt,         (GLUniformType)(GL_UNIFORM_INT1   + (i / 2)), isArray ? 2 : 1));
		ASSERT_TRUE(shaderProgram.SetUniform(uintStr.c_str(),  inUnsignedInt, (GLUniformType)(GL_UNIFORM_UINT1  + (i / 2)), isArray ? 2 : 1));
		ASSERT_TRUE(shaderProgram.SetUniform(floatStr.c_str(), inFloat,       (GLUniformType)(GL_UNIFORM_FLOAT1 + (i / 2)), isArray ? 2 : 1));
		
		ASSERT_TRUE(shaderProgram.GetUniformData(intStr.c_str(),   outInt,      (GLUniformType)(GL_UNIFORM_INT1   + (i / 2)), isArray ? 2 : 1));
		ASSERT_TRUE(shaderProgram.GetUniformData(uintStr.c_str(),  outUnsigned, (GLUniformType)(GL_UNIFORM_UINT1  + (i / 2)), isArray ? 2 : 1));
		ASSERT_TRUE(shaderProgram.GetUniformData(floatStr.c_str(), outFloat,    (GLUniformType)(GL_UNIFORM_FLOAT1 + (i / 2)), isArray ? 2 : 1));

		EXPECT_TRUE(CompareVals<int>         (outInt,      inInt,         sizeArray[i]));
		EXPECT_TRUE(CompareVals<unsigned int>(outUnsigned, inUnsignedInt, sizeArray[i]));
		EXPECT_TRUE(CompareVals<float>       (outFloat,    inFloat,       sizeArray[i]));
	}

	// Now test all the matrices
	ASSERT_TRUE(shaderProgram.SetUniform("inMat2V", inFloat, GL_UNIFORM_MAT2, 8));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat2V", outFloat, GL_UNIFORM_MAT2, 8));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 8));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat3V", inFloat, GL_UNIFORM_MAT3, 18));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat3V", outFloat, GL_UNIFORM_MAT3, 18));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 32));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat4V", inFloat, GL_UNIFORM_MAT4, 32));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat4V", outFloat, GL_UNIFORM_MAT4, 32));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 32));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat2x3V", inFloat, GL_UNIFORM_MAT2x3, 12));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat2x3V", outFloat, GL_UNIFORM_MAT2x3, 12));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 12));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat2x4V", inFloat, GL_UNIFORM_MAT2x4, 16));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat2x4V", outFloat, GL_UNIFORM_MAT2x4, 16));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 16));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat3x4V", inFloat, GL_UNIFORM_MAT3x4, 24));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat3x4V", outFloat, GL_UNIFORM_MAT3x4, 24));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 24));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat3x2V", inFloat, GL_UNIFORM_MAT3x2, 12));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat3x2V", outFloat, GL_UNIFORM_MAT3x2, 12));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 12));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat4x3V", inFloat, GL_UNIFORM_MAT4x3, 24));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat4x3V", outFloat, GL_UNIFORM_MAT4x3, 24));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 24));

	ASSERT_TRUE(shaderProgram.SetUniform("inMat4x2V", inFloat, GL_UNIFORM_MAT4x2, 16));
	ASSERT_TRUE(shaderProgram.GetUniformData("inMat4x2V", outFloat, GL_UNIFORM_MAT4x2, 16));
	EXPECT_TRUE(CompareVals<float>(outFloat, inFloat, 16));
}