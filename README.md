# Table of Contents
- [Introduction](#introduction)
- [Getting Started](#getting-started)

# Introduction
OpenGL is a well-known, widely used graphics library. Created in 1992, it's purpose has been to provide the user a cross-platform api to render graphics through the gpu. However, much like other graphics libraries, there is considerable setup to getting a basic application running which can prove daunting to new users. That's where OpenGLLib comes in.

OpenGLLib is a wrapper that abstract's much of the core functionality away into a handful of classes. This way, the user just needs to pass the settings they require, the data they need to render, and start the usual rendering process.

It is recommended that the user should still have a good understanding how OpenGL works. This is because in the current version of this library, there are still a few calls that the user will need to use (glfwPollEvents and glDrawArrays to name a few). Additionally, because of the state based nature, it would be helpful for the purpose of debugging. Some recommended resources to review would be [learnopengl.com](https://www.learnopengl.com) and the [Khronos OpenGL Wiki](https://www.khronos.org/opengl/wiki/).

It should be noted that OpenGLLib is **NOT** a direct replacement of OpenGL itself, nor is this part of the standard library and not contributed by the Khronos group in anyway. This is an open-source effort to assist other into either getting started with their application faster or to assist others in how the api works.

# Getting Started
OpenGLLib is built using Microsoft Visual Studio 2022 in a Windows 11 environment. Be aware that this library has not been tested on previous versions of Microsoft Visual Studio or on other Operating Systems. Plans are in the works to make this cross-platform.

To use, clone this library into a directory and open the OpenGLLib.sln file. From there, at the top of the page go to Build > Build Solution. To view the samples, go to Solution Explorer > right click OpenGLLibSamples > Set as Startup Project and click Local Windows Debugger at the top. You should see a borderless window appear in the top-right corner with a green triangle.
