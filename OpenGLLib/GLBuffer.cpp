#include "GLBuffer.h"

GLBuffer::GLBuffer()
{
	glGenVertexArrays(1, &_arrayObject);
}

GLBuffer::~GLBuffer()
{

}

void GLBuffer::BindVertexArray()
{
	glBindVertexArray(_arrayObject);
}

void GLBuffer::BindBuffer(unsigned int index)
{
	glBindBuffer(_bufferVector.at(index)._bufferType, _bufferVector.at(index)._bufferObject);
}

bool GLBuffer::IsVertexArrayBound()
{
	int data;

	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &data);
	
	if (data == 0)
	{
		return false;
	}

	return _arrayObject == data;
}

bool GLBuffer::IsBufferBound(unsigned int index)
{
	int data;
	GLenum bufferType = _bufferVector.at(index)._bufferType == GL_ARRAY_BUFFER ? GL_ARRAY_BUFFER_BINDING : GL_ELEMENT_ARRAY_BUFFER_BINDING;

	glGetIntegerv(bufferType, &data);

	if (data == 0)
	{
		return false;
	}

	return _bufferVector.at(index)._bufferObject == data;
}

void GLBuffer::AddBuffer(GLenum bufferType)
{
	BufferInfo info;
	info._bufferType = bufferType;

	glGenBuffers(1, &info._bufferObject);

	_bufferVector.push_back(info);
}

void GLBuffer::AddAttribPointer(unsigned int bufferIndex, unsigned int attributeIndex, unsigned int numComponents, GLenum valueType, GLboolean normalized, unsigned int strideSize, unsigned int componentOffset)
{
	BindVertexArray();
	BindBuffer(bufferIndex);
	glVertexAttribPointer(attributeIndex, numComponents, valueType, normalized, strideSize, (void*)componentOffset);
}

void GLBuffer::EnableAttribPointer(unsigned int bufferIndex, unsigned int attributeIndex, bool activate)
{
	BindVertexArray();
	BindBuffer(bufferIndex);
	activate ? glEnableVertexAttribArray(attributeIndex) : glDisableVertexAttribArray(attributeIndex);
}

unsigned int GLBuffer::GetBuffer(unsigned int index) const
{
	return _bufferVector[index]._bufferObject; // For the current implementation, return the max possible unsigned integer value;
}

void GLBuffer::SetBufferData(unsigned int bufferIndex, void* data, unsigned int dataSize, GLenum drawType)
{
	BindVertexArray();
	BindBuffer(bufferIndex);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, drawType);
}