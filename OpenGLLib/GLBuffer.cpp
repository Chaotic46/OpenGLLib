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

void GLBuffer::AddBuffer(GLenum bufferType, unsigned int numComponents, GLenum valueType, GLboolean normalized, unsigned int strideSize, unsigned int componentOffset)
{
	AddBuffer(bufferType);

	ModifyAttribPointer(_bufferVector.size() - 1, numComponents, valueType, normalized, strideSize, componentOffset);
}

void GLBuffer::ModifyAttribPointer(unsigned int index, unsigned int numComponents, GLenum valueType, GLboolean normalized, unsigned int strideSize, unsigned int componentOffset)
{
	BindVertexArray();

	BindBuffer(index);

	glVertexAttribPointer(index, numComponents, valueType, normalized, strideSize, (void*)componentOffset);

	glEnableVertexAttribArray(index);
}

