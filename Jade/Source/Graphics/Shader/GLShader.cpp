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

bool Jade::Graphics::GLShader::Create(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Compute:
		computeShader = glCreateShader(GL_COMPUTE_SHADER);
		break;
	case ShaderType::Domain:
		evaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	case ShaderType::Geometry:
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case ShaderType::Pixel:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::Tesselation:
		controlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case ShaderType::Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	default: return false;
	}

	GLSLShader result;
	int id = TranslateHLSLFromFile(filename.c_str(), 0, LANG_440, nullptr, &dependencies, &result);

	if (id != 0)
	{
		program = glCreateProgram();

		glShaderSource(shader, 1, const_cast<const char **>(&result.sourceCode), nullptr);
		glCompileShader(shader);

		bool check;
		check = CheckForErrors(shader, GL_COMPILE_STATUS, false, "Shader Compilation Error: ");
		if (check == false)
			return false;

		glAttachShader(program, shader);
		glLinkProgram(program);
		check = CheckForErrors(program, GL_LINK_STATUS, true, "Shader Linking Error : ");
		if (check == false)
			return false;

		glValidateProgram(program);
		CheckForErrors(program, GL_VALIDATE_STATUS, true, "Shader Validation Error : ");
		if (check == false)
			return check;

		glDetachShader(program, shader);
		glDeleteShader(shader);

		glUseProgram(program);

		FreeGLSLShader(&result);

		return true;
	}

	return false;

	return false;
}

bool Jade::Graphics::GLShader::Release()
{
	glDeleteProgram(program);

	return true;
}

/*
bool Jade::Graphics::GLShader::Compile(std::string filename, ShaderType type)
{

}
*/

bool Jade::Graphics::GLShader::CheckForErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof error, nullptr, error);
		else
			glGetShaderInfoLog(shader, sizeof error, nullptr, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;

		return false;
	}

	return true;
}

GLuint Jade::Graphics::GLShader::GetShaderFromType(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Compute:
		return computeShader;
	case ShaderType::Domain:
		return evaluationShader;
	case ShaderType::Geometry:
		return geometryShader;
	case ShaderType::Pixel:
		return fragmentShader;
	case ShaderType::Tesselation:
		return controlShader;
	case ShaderType::Vertex:
		return vertexShader;
	default:
		return 0;
	}
}