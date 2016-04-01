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

#include "Graphics/Shader/Shader.h"

std::shared_ptr<Jade::Graphics::IShader> Jade::Graphics::Shader::CreateShader(Device device, std::map<std::string, ShaderType> shaders)
{
	switch (device.GetGraphicsAPI())
	{
	case GraphicsAPI::DirectX:
		return std::make_shared<TestDXShader>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()), shaders);
	case GraphicsAPI::OpenGL:
		return std::make_shared<GLShader>(filename, type);
	case GraphicsAPI::Vulkan:
		break;
	}

	return nullptr;
}

std::shared_ptr<Jade::Graphics::IShader> Jade::Graphics::Shader::CreateShader(std::shared_ptr<Device> device, std::string filename, ShaderType type)
{
	switch (device->GetGraphicsAPI())
	{
		case GraphicsAPI::DirectX:
			return std::make_shared<DXShader>(std::dynamic_pointer_cast<DXDevice>(device->GetIDevice()), filename, type);
		case GraphicsAPI::OpenGL:
			return std::make_shared<GLShader>(filename, type);
		case GraphicsAPI::Vulkan:
			break;
	}

	return nullptr;
}
