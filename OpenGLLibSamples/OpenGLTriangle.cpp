#include "../OpenGLLib/GLWindow.h"
#include "../OpenGLLib/GLShader.h"
#include "../OpenGLLib/GLEngine.h"
#include "../OpenGLLib/GLBuffer.h"

#include "Shaders.h"

#include <iostream>

int main()
{
	GLWindow triangleWindow(GLSize(400, 300), "OpenGLLib Triangle");
	GLShader shader;
	GLBuffer buffer;
	GLEngine* engine = GLEngine::GetInstance();

	float bufferData[] = {
		// position   // color
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	shader.CreateVertex(vertexShader);
	shader.CreateFragment(fragmentShader);
	shader.LinkProgram();

	buffer.AddBuffer(GL_ARRAY_BUFFER);
	buffer.AddAttribPointer(0, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	buffer.AddAttribPointer(0, 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 2 * sizeof(float));
	buffer.EnableAttribPointer(0, 0);
	buffer.EnableAttribPointer(0, 1);
	buffer.SetBufferData(0, bufferData, sizeof(bufferData), GL_STATIC_DRAW);

	engine->PushGLWindow(&triangleWindow);
	engine->StartThread();

	while (1)
	{
		shader.UseProgram();
		buffer.BindVertexArray();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
	}

	return 0;
}