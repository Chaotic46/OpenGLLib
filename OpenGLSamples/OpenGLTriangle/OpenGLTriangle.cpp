#include "../../OpenGLLib/GLWindow.h"
#include "../../OpenGLLib/GLShader.h"
#include "../../OpenGLLib/GLEngine.h"
#include "../../OpenGLLib/GLBuffer.h"

#include "Shaders.h"

#include <iostream>

void AttachShadersAndBuffers(GLWindow & window)
{
	GLShader* shader = new GLShader;
	GLBuffer* buffer = new GLBuffer;

	GLenum err = glGetError();
	float bufferData[] = {
		// position   // color
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	};
	
	// Setup shader
	shader->CreateVertex(vertexShader);
	shader->CreateFragment(fragmentShader);
	shader->LinkProgram();

	// Setup buffer
	buffer->AddBuffer(GL_ARRAY_BUFFER);

	buffer->AddAttribPointer(0, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	buffer->AddAttribPointer(0, 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 2 * sizeof(float));

	buffer->EnableAttribPointer(0, 0);
	buffer->EnableAttribPointer(0, 1);

	buffer->SetBufferData(0, bufferData, sizeof(bufferData), GL_STATIC_DRAW);

	// Attach buffer to shader
	shader->AttachBuffer(buffer);

	// Attach shader to window
	window.AttachShader(shader);
}

int main()
{
	GLWindow triangleWindow1(GLSize(1080, 920), "OpenGLLib Triangle 1");
	GLWindow triangleWindow2(GLSize(1080, 920), "OpenGLLib Triangle 2");
	GLEngine* engine = GLEngine::GetInstance();

	triangleWindow1.SetCurrentContext();
	AttachShadersAndBuffers(triangleWindow1);

	triangleWindow2.SetCurrentContext();
	AttachShadersAndBuffers(triangleWindow2);

	// Detach any contexts as it will need to be used in the GLEngine thread.
	glfwMakeContextCurrent(NULL);

	// Push the window to the GLEngine
	engine->PushGLWindow(&triangleWindow1);
	engine->PushGLWindow(&triangleWindow2);
	engine->StartThread();

	while (1)
	{
		triangleWindow1.SwapBuffers();
		triangleWindow2.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}