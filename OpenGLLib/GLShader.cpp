#include "GLShader.h"

GLShader::GLShader() : _vertex(0),
                       _fragment(0),
                       _geometry(0),
                       _program(0)
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

void GLShader::AttachBuffer(const GLBuffer* buffer)
{
	
}

GLBuffer* GLShader::GetAttachedBuffer() const
{
	return NULL;
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