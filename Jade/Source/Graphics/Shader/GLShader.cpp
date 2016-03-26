/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Graphics/Shader/GLShader.h>
#include <iostream>

bool Jade::Graphics::GLShader::Create()
{
	std::cout << glGetString(GL_VERSION) << std::endl;

	switch (type)
	{
	case ShaderType::Compute:
		shader = glCreateShader(GL_COMPUTE_SHADER);
		break;
	case ShaderType::Domain:
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	case ShaderType::Geometry:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case ShaderType::Pixel:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::Tesselation:
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case ShaderType::Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	default: break;
	}

	return shader != 0 ? true : false;
}

bool Jade::Graphics::GLShader::Release()
{
	return false;
}

bool Jade::Graphics::GLShader::Compile()
{
	GLSLShader result;
	int id = TranslateHLSLFromFile(filename.c_str(), 0, LANG_440, nullptr, &dependencies, &result);
	
	return true;
}
