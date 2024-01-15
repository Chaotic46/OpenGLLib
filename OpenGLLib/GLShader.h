#ifndef GLSHADER_H_
#define GLSHADER_H_

#include "GLCommon.h"
#include "GLBuffer.h"

class GLShader
{
public:
	GLShader();
	~GLShader();

	bool CreateVertex(const char * shader);
	bool CreateFragment(const char* shader);
	bool CreateGeometry(const char* geometry);
	bool LinkProgram();

	void UseProgram();
	bool IsProgramUsed();
	
	void AttachBuffer(GLBuffer * buffer);
	GLBuffer* GetAttachedBuffer() const;

	bool SetUniform(const char * uniform, void * uniformData, GLUniformType uniformType, unsigned int count = 1);
	bool GetUniformData(const char * uniform, void * uniformData, GLUniformType uniformType, unsigned int size = 0);

private:
	bool CreateShader(unsigned int& shaderID, GLenum shaderType, const char* shaderProgram);
	void DetachShader(unsigned int shaderID);
	bool IsShaderAttached(unsigned int shaderID);

	unsigned int _vertex;
	unsigned int _fragment;
	unsigned int _geometry;
	unsigned int _program;

	GLBuffer * _buffer;
};

#endif