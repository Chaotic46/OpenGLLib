#ifndef GLSHADER_H_
#define GLSHADER_H_

class GLShader
{
public:
	GLShader();
	~GLShader();

	bool AttachVertex(const char * shader);
	bool AttachFragment(const char* shader);
	bool LinkProgram();

private:
	unsigned int _vertex;
	unsigned int _fragment;
	unsigned int _program;
};

#endif