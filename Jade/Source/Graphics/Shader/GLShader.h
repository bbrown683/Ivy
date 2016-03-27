#pragma once

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

// Define before inclusion if on windows systems.
#ifdef _WIN32
#define USE_STDINT
#endif
#include "hlslcc/hlslcc.h"

#include <Core/Utility.h>
#include <Graphics/Device/GLDevice.h>
#include <Graphics/Shader/IShader.h>
#include <Graphics/Shader/ShaderType.h>

namespace Jade
{
	namespace Graphics
	{
		class GLShader : public IShader
		{
		private:

			std::unordered_map<std::string, ShaderType> shaders;
			
			std::string filename;
			ShaderType type;

			// Possible shaders.
			GLuint shader;
			GLuint computeShader;
			GLuint controlShader;
			GLuint evaluationShader;
			GLuint fragmentShader;
			GLuint geometryShader;
			GLuint vertexShader;

			GLuint program;
			GLSLCrossDependencyData dependencies;

			bool Create(ShaderType type) override;
			bool Release() override;
			bool CheckForErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
			GLuint GetShaderFromType(ShaderType type);

		public:

			GLShader(std::unordered_map<std::string, ShaderType> shaders)
			{
				this->shaders = shaders;
				
				for (int i = 0; i < shaders.size(); i++)
				{
					
				}
			}

			GLShader(std::string filename, ShaderType type)
			{
				this->filename = filename;
				this->type = type;

				GLShader::Create(type);
			}

			~GLShader()
			{
				GLShader::Release();
			}
		};
	}
}
