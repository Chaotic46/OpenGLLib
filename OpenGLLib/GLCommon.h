#ifndef GLCOMMON_H_
#define GLCOMMON_H_

#include <utility>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

typedef std::pair<int, int> GLSize;

/* \brief Struct to handle the color components for the background of a window.
 */
struct GLRGBA
{
public:
	GLRGBA() : _r(0.0f), _g(0.0f), _b(0.0f), _a(0.0f) {}
	GLRGBA(float r, float g, float b, float a)
	{
		SetR(r);
		SetG(g);
		SetB(b);
		SetA(a);
	}

	friend bool operator==(const GLRGBA& colour1, const GLRGBA& colour2)
	{
		return (colour1._r == colour2._r) && (colour1._g == colour2._g) && (colour1._b == colour2._b) && (colour1._a == colour2._a);
	}

	void SetR(float r) { _r = BoundCheck(r); }
	void SetG(float g) { _g = BoundCheck(g); }
	void SetB(float b) { _b = BoundCheck(b); }
	void SetA(float a) { _a = BoundCheck(a); }

	float GetR() const { return _r; }
	float GetG() const { return _g; }
	float GetB() const { return _b; }
	float GetA() const { return _a; }
private:
	float BoundCheck(float input)
	{
		return (input > 1.0f ? 1.0f : input < 0.0f ? 0.0f : input);
	}

	float _r;
	float _g;
	float _b;
	float _a;
};

/* \brief Enum to represent the glfw hints when creating a window.
 */
enum GLHints
{
	GL_RESIZABLE     = 0x01,
	GL_VISIBLE       = 0x02,
	GL_DECORATED     = 0x04,
	GL_FOCUSED       = 0x08,
	GL_AUTO_MINIMIZE = 0x10,
	GL_FLOATING      = 0x20,
	GL_MAXIMIZED     = 0x40,
	GL_FOCUS_ON_SHOW = 0x80,

	GL_DEFAULT       = GL_RESIZABLE | GL_VISIBLE | GL_DECORATED | GL_FOCUSED | GL_FOCUS_ON_SHOW,
};
#endif