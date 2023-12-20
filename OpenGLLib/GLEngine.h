#ifndef OPENGLENGINE_H_
#define OPENGLENGINE_H_

class GLEngine
{
public:
	static GLEngine* GetInstance();

private:
	GLEngine();
	~GLEngine();
};

#endif