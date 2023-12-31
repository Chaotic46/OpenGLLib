#include "../OpenGLLib/GLWindow.h"
#include "../OpenGLLib/GLShader.h"
#include "../OpenGLLib/GLEngine.h"
#include "../OpenGLLib/GLBuffer.h"

#include "Shaders.h"

#include <iostream>

int main()
{
	GLWindow triangleWindow(GLSize(1080, 920), "OpenGLLib Triangle");
	GLShader * shader = new GLShader;
	GLEngine * engine = GLEngine::GetInstance();
	GLBuffer buffer;

	float bufferData[] = {
		// position   // color
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	};

	shader->CreateVertex(vertexShader);
	shader->CreateFragment(fragmentShader);
	shader->LinkProgram();

	buffer.AddBuffer(GL_ARRAY_BUFFER);
	buffer.AddAttribPointer(0, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	buffer.AddAttribPointer(0, 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 2 * sizeof(float));
	buffer.EnableAttribPointer(0, 0);
	buffer.EnableAttribPointer(0, 1);
	buffer.SetBufferData(0, bufferData, sizeof(bufferData), GL_STATIC_DRAW);

	triangleWindow.AttachShader(shader);

	// Detach any contexts as it will need to used in the GLEngine thread.
	glfwMakeContextCurrent(NULL);

	engine->PushGLWindow(&triangleWindow);
	engine->StartThread();

	while (1)
	{
		buffer.BindVertexArray();
		triangleWindow.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}