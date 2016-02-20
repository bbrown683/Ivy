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

#include "Graphics/Window/Window.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Shader/Shader.h"

using Jade::Graphics::Window;
using Jade::Graphics::Device;
using Jade::Graphics::Shader;

int main(int argc, char* argv[])
{
	// Creates a basic window that can be rendered to with either graphics API.
	std::shared_ptr<Window> window = std::make_shared<Window>(Window(1080, 720, 100, 100, "Hello World", false));

	// Creates an OpenGL or DirectX device depending on window type.
	std::shared_ptr<Device> device = std::make_shared<Device>(Device(window));

	// Create our two required shaders for drawing onto the surface.
	std::shared_ptr<Shader>	fragmentShader = std::make_shared<Shader>(Shader("fragment.hlsl"));
	std::shared_ptr<Shader>	pixelShader = std::make_shared<Shader>(Shader("pixel.hlsl"));

	while (window->IsOpen())
	{
		// Rendering
		device->Clear(Jade::Math::Color(Jade::Math::Color::CornflowerBlue));

		// Updating
		device->Present();
		window->PollEvents();
	}

	return 0;
}