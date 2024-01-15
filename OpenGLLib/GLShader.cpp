#include "GLShader.h"

GLShader::GLShader() : _vertex(0),
                       _fragment(0),
                       _geometry(0),
                       _program(0),
                       _buffer(NULL)
{

}

GLShader::~GLShader()
{
	if (_vertex)
	{
		DetachShader(_vertex);
		glDeleteShader(_vertex);
	}

	if (_fragment)
	{
		DetachShader(_fragment);
		glDeleteShader(_fragment);
	}

	if (_program)
	{
		glDeleteProgram(_program);
	}
}

/* \brief Creates a new fragment shader. This will preemptively detach the fragment shader from an existing shader program.
 */
bool GLShader::CreateVertex(const char* shader)
{
	return CreateShader(_vertex, GL_VERTEX_SHADER, shader);
}

/* \brief Creates a new fragment shader. This will preemptively detach the fragment shader from an existing shader program.
 */
bool GLShader::CreateFragment(const char* shader)
{
	return CreateShader(_fragment, GL_FRAGMENT_SHADER, shader);
}

/* \brief Creates a new geometry shader. This will preemptively detach the fragment shader from an existing shader program.
 */
bool GLShader::CreateGeometry(const char* shader)
{
	return CreateShader(_geometry, GL_GEOMETRY_SHADER, shader);
}

/* \brief Creates a new shader program if one does not exists and links the created shaders.
 */
bool GLShader::LinkProgram()
{
	int success = 0;

	if (!_program)
	{
		_program = glCreateProgram();
	}

	// Did the user create a vertex shader? (required)
	if (!_vertex)
	{
		return false;
	}
	else
	{
		DetachShader(_vertex);
	}

	// Did the user create a fragment shader? (required)
	if (!_fragment)
	{
		return false;
	}
	else
	{
		DetachShader(_fragment);
	}

	// Did the user create a fragment shader? (optional)
	if (_geometry)
	{
		DetachShader(_geometry);
		glAttachShader(_program, _geometry);
	}

	glAttachShader(_program, _vertex);
	glAttachShader(_program, _fragment);

	glLinkProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &success);

	return success;
}

/* \brief Uses the current program in GLShader.
 */
void GLShader::UseProgram()
{
	glUseProgram(_program);
}

/* \brief Checks if GLShader's program is in use.
 */
bool GLShader::IsProgramUsed()
{
	int program = 0;

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	if (program == 0)
	{
		return false;
	}
	else if (_program != program)
	{
		return false;
	}

	return true;
}

void GLShader::AttachBuffer(GLBuffer* buffer)
{
	_buffer = buffer;
}

GLBuffer* GLShader::GetAttachedBuffer() const
{
	return _buffer;
}

bool GLShader::SetUniform(const char* uniform, void* uniformData, GLUniformType uniformType, unsigned int count)
{
	int location = glGetUniformLocation(_program, uniform);

	if (location < -1)
	{
		return false;
	}

	switch (uniformType)
	{
		case(GL_UNIFORM_INT1): glUniform1iv(location, count, (GLint*)uniformData); break;
		case(GL_UNIFORM_INT2): glUniform2iv(location, count, (GLint*)uniformData); break;
		case(GL_UNIFORM_INT3): glUniform3iv(location, count, (GLint*)uniformData); break;
		case(GL_UNIFORM_INT4): glUniform4iv(location, count, (GLint*)uniformData); break;

		case(GL_UNIFORM_UINT1): glUniform1uiv(location, count, (GLuint*)uniformData); break;
		case(GL_UNIFORM_UINT2): glUniform2uiv(location, count, (GLuint*)uniformData); break;
		case(GL_UNIFORM_UINT3): glUniform3uiv(location, count, (GLuint*)uniformData); break;
		case(GL_UNIFORM_UINT4): glUniform4uiv(location, count, (GLuint*)uniformData); break;

		case(GL_UNIFORM_FLOAT1): glUniform1fv(location, count, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_FLOAT2): glUniform2fv(location, count, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_FLOAT3): glUniform3fv(location, count, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_FLOAT4): glUniform4fv(location, count, (GLfloat*)uniformData); break;

		case(GL_UNIFORM_MAT2):   glUniformMatrix2fv  (location, count, false, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_MAT2x3): glUniformMatrix2x3fv(location, count, false, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_MAT2x4): glUniformMatrix2x4fv(location, count, false, (GLfloat*)uniformData); break;

		case(GL_UNIFORM_MAT3):   glUniformMatrix3fv  (location, count, false, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_MAT3x2): glUniformMatrix3x2fv(location, count, false, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_MAT3x4): glUniformMatrix3x4fv(location, count, false, (GLfloat*)uniformData); break;

		case(GL_UNIFORM_MAT4):   glUniformMatrix4fv  (location, count, false, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_MAT4x2): glUniformMatrix4x2fv(location, count, false, (GLfloat*)uniformData); break;
		case(GL_UNIFORM_MAT4x3): glUniformMatrix4x3fv(location, count, false, (GLfloat*)uniformData); break;
	}

	return true;
}

bool GLShader::GetUniformData(const char* uniform, void* uniformData, GLUniformType uniformType, unsigned int size)
{
	int location = glGetUniformLocation(_program, uniform);

	if (location < -1)
	{
		return false;
	}

	return true;
}

/* \brief Creates a new shader. This will preemptively detach the shader if it is already attached to a shader program.
 */
bool GLShader::CreateShader(unsigned int& shaderID, GLenum shaderType, const char* shaderProgram)
{
	int  success = 0;

	if (!shaderID)
	{
		shaderID = glCreateShader(shaderType);
	}
	else
	{
		DetachShader(shaderID);
	}

	glShaderSource(shaderID, 1, &shaderProgram, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	return success;
}

/* \brief Detaches the shader if it is attached to the shader program
 */
void GLShader::DetachShader(unsigned int shaderID)
{
	if (_program && IsShaderAttached(shaderID))
	{
		glDetachShader(_program, shaderID);
	}
}

/* \brief Checks if the given shader is attached to the shader program.
 */
bool GLShader::IsShaderAttached(unsigned int shaderID)
{
	// 3 as the user can add a vertex, fragment, and geometry shader.
	const int maxCount = 3;
	unsigned int shaders[maxCount];
	int shadersBeingUsed;

	if (_program)
	{
		glGetAttachedShaders(_program, maxCount, &shadersBeingUsed, shaders);

		for (unsigned int i = 0; i < shadersBeingUsed; i++)
		{
			if (shaders[i] == shaderID)
			{
				return true;
			}
		}
	}

	return false;
}