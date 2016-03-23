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

#include <iostream>

#include "System/Window/Window.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Mesh/Mesh.h"

using Jade::Graphics::Device;
using Jade::Graphics::Shader;
using Jade::Graphics::Mesh;
using Jade::Math::Color;
using Jade::Math::Vector3;
using Jade::Math::Vertex;
using Jade::System::Key;
using Jade::System::Window;

int main(int argc, char* argv[])
{
	// Creates a basic window that can be rendered with either graphics API.
	std::shared_ptr<Window> window = std::make_shared<Window>(1080, 720, 100, 100, "Hello World", false);

	// Creates a graphics device.
	std::shared_ptr<Device> device = std::make_shared<Device>(window, Jade::Graphics::GraphicsAPI::OpenGL);

	// Create our two required shaders for drawing onto the surface.
	std::shared_ptr<Shader>	vertexShader = std::make_shared<Shader>(".\\resources\\shaders\\vertex.hlsl", Jade::Graphics::ShaderType::Vertex, device);
	std::shared_ptr<Shader>	pixelShader = std::make_shared<Shader>(".\\resources\\shaders\\pixel.hlsl", Jade::Graphics::ShaderType::Pixel, device);

	// Create some vertices for our triangle.
	/*
	std::vector<Vertex> vertices = {
		{ Vector3(0.0f, 0.5f, 0.5f), Color::Red },
		{ Vector3(0.5f, -0.5f, 0.5f), Color::Green },
		{ Vector3(-0.5f, -0.5f, 0.5f), Color::Blue } };

	std::vector<unsigned int> indices = { 0, 1, 2 };
	*/

	std::vector<Vertex> vertices =
	{
		{ Vector3(-1.0f, 1.0f, -1.0f), Color::Red },
		{ Vector3(1.0f, 1.0f, -1.0f), Color::Green },
		{ Vector3(1.0f, 1.0f, 1.0f), Color::Blue },
		{ Vector3(-1.0f, 1.0f, 1.0f), Color::White },
		{ Vector3(-1.0f, -1.0f, -1.0f), Color::Black },
		{ Vector3(1.0f, -1.0f, -1.0f), Color::Purple },
		{ Vector3(1.0f, -1.0f, 1.0f), Color::Yellow },
		{ Vector3(-1.0f, -1.0f, 1.0f), Color::Magenta },
	};

	std::vector<unsigned int> indices =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};
	
	// Creates and binds the vertex buffer for drawing the triangular mesh.
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices, device);

	while (window->IsOpen())
	{
		// Rendering
		device->Clear(Color::CornflowerBlue);

		// Draw the vertices.
		mesh->Draw();

		// Updating if escape is not pressed.
		if (window->IsKeyDown(Key::Escape))
		{
			window->Close();
		}
		else
		{
			device->Present();
			window->PollEvents();
		}
	}

	return 0;
}