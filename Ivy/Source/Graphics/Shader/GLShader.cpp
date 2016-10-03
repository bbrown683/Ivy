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

#include "Graphics/Shader/GLShader.h"
#include "System/File.h"

bool Ivy::Graphics::GLShader::Create(istring filename, ShaderType type)
{	
    GLuint shader;
    
    switch (type)
    {
    case ShaderType::Pixel:
        std::cout << "[Fragment Shader]" << std::endl;
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    case ShaderType::Vertex:
        std::cout << "[Vertex Shader]" << std::endl;
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    default: return false;
    }

    // Read the file into a string.
    /*
    System::File file(filename);
    std::string data = file.Read();

    // Print out shader code for debugging purposes.
    std::cout << data << std::endl;

    // glShaderSource needs a const char* of our file data.
    const char* source = data.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Used to print errors if there are any.
    std::string buffer;
    if(Check(shader, GL_COMPILE_STATUS, false, buffer))
    {
        shaderIDs.push_back(shader);

        return true;
    }

    */
    return false;
}

bool Ivy::Graphics::GLShader::Compile(istring filename, ShaderType type)
{
    return false;
}

bool Ivy::Graphics::GLShader::Release()
{
    glDeleteProgram(programID);
   
    return true;
}

bool Ivy::Graphics::GLShader::Check(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

bool Ivy::Graphics::GLShader::CheckShader(GLuint shader)
{
    return false;
}

bool Ivy::Graphics::GLShader::CheckProgram(GLuint program)
{
    return false;
}

void Ivy::Graphics::GLShader::MakeActive()
{
    glUseProgram(programID);
}

void Ivy::Graphics::GLShader::MakeInactive()
{

}

bool Ivy::Graphics::GLShader::CreateProgram()
{
    programID = glCreateProgram();
    
    for (unsigned int i = 0; i < shaderIDs.size(); i++)
        glAttachShader(programID, shaderIDs[i]);

    std::cout << "[Program]" << std::endl;

    // After all shaders are attached, 
    // we can now link them to a single program.
    glLinkProgram(programID);
    
    std::string buffer;
    if (Check(programID, GL_LINK_STATUS, true, buffer))
    {
        std::cout << "Program was linked successfully." << std::endl;

        for (unsigned int i = 0; i < shaderIDs.size(); i++)
        {
            // Detach shaders from program and mark them for deletion.
            glDetachShader(programID, shaderIDs[i]);
            glDeleteShader(shaderIDs[i]);
        }

        // Lastly we validate the program can execute.
        glValidateProgram(programID);

        if (Check(programID, GL_VALIDATE_STATUS, true, buffer))
        {
            std::cout << "Program was validated successfully." << std::endl;

            return true;
        }
    }

    return false;
}

GLuint Ivy::Graphics::GLShader::GetProgramID()
{
    return programID;
}
