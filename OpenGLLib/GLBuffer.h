#ifndef GLBUFFER_H_
#define GLBUFFER_H_

#include <vector>

#include "GLCommon.h"

class GLBuffer
{
public:
	GLBuffer();
	~GLBuffer();

	void BindVertexArray();
	void BindBuffer(unsigned int index);

	bool IsVertexArrayBound();
	bool IsBufferBound(unsigned int index);

	void AddBuffer(GLenum bufferType);
	void AddAttribPointer(unsigned int bufferIndex, unsigned int attributeIndex, unsigned int numComponents, GLenum valueType, GLboolean normalized, unsigned int strideSize, unsigned int componentOffset);

	void EnableAttribPointer(unsigned int bufferIndex, unsigned int attributeIndex, bool activate = true);

	unsigned int GetBuffer(unsigned int index) const;

private:
	struct BufferInfo
	{
		unsigned int _bufferObject;
		GLenum       _bufferType;
	};

	std::vector<BufferInfo> _bufferVector;
	unsigned int _arrayObject;
};

#endif