#ifndef GLSHADER_H_
#define GLSHADER_H_

#include "GLCommon.h"

class GLShader
{
public:
	GLShader();
	~GLShader();

	bool CreateVertex(const char * shader);
	bool CreateFragment(const char* shader);
	bool CreateGeometry(const char* geometry);
	bool LinkProgram();

private:
	bool CreateShader(unsigned int& shaderID, GLenum shaderType, const char* shaderProgram);
	void DetachShader(unsigned int shaderID);
	bool IsShaderAttached(unsigned int shaderID);

	unsigned int _vertex;
	unsigned int _fragment;
	unsigned int _program;
};

#endif