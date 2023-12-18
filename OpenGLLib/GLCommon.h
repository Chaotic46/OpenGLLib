#ifndef GLCOMMON_H_
#define GLCOMMON_H_

#include <utility>

typedef std::pair<int, int> GLSize;

struct GLRGBA
{
public:
	GLRGBA() {}
	GLRGBA(float r, float g, float b, float a) {}

	void SetR(float r) {}
	void SetG(float g) {}
	void SetB(float b) {}
	void SetA(float a) {}

	float GetR() const {return 0.0f;}
	float GetG() const {return 0.0f;}
	float GetB() const {return 0.0f;}
	float GetA() const {return 0.0f;}
private:
	float _r;
	float _g;
	float _b;
	float _a;
};

#endif