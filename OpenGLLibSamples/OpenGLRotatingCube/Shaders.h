#ifndef SHADERS_H_
#define SHADERS_H_

const char* vertexShader =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 shaderColor;\n"
""
"out vec3 fragShaderColor;\n"
""
"void main()\n"
"{\n"
"	fragShaderColor = shaderColor;\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const char* fragmentShader =
"#version 330 core\n"
""
"in vec3 fragShaderColor;\n"
""
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vec4(fragShaderColor.xyz, 1.0f);\n"
"}\n";

#endif