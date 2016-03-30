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
#include "Graphics/Model/Model.h"

using namespace Jade::Core;
using namespace Jade::Graphics;
using namespace Jade::Math;
using namespace Jade::System;

int main(int argc, char* argv[])
{
	// Creates a basic window that can be rendered with either graphics API.
	std::shared_ptr<Window> window = std::make_shared<Window>(1080, 720, 100, 100, "Hello World", false);

	// Creates a graphics device.
	std::shared_ptr<Device> device = std::make_shared<Device>(window, GraphicsAPI::DirectX);

	// Key value pair for shader filename and what type they are.
	std::unordered_map<std::string, ShaderType> shaders =
	{
		{ ".\\resources\\shaders\\vertex.cso", ShaderType::Vertex },
		{ ".\\resources\\shaders\\pixel.cso", ShaderType::Pixel },
	};

	std::shared_ptr<Shader>	shader = std::make_shared<Shader>(device, shaders);

	// Create some vertices for our triangle.
	
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

	//std::shared_ptr<Model> model = std::make_shared<Model>(device);
	//model->Load(".\\resources\\models\\teapot.obj");

	// Creates and binds the vertex buffer for drawing the triangular mesh.
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(device, vertices, indices);

	while (window->IsOpen())
	{
		// Rendering
		device->Clear(Color::CornflowerBlue);

		// Draw the vertices.
		mesh->Draw();
		//model->Draw();

		// Gets the keys pressed and prints their enumerication value that is stored as an integer.
		std::vector<Key> keysPressed = window->GetInput().keyboard.GetKeysPressed();
		for (unsigned int i = 0; i < keysPressed.size(); i++)
			std::cout << static_cast<int>(keysPressed[i]) << std::endl;
		
		// Updating if escape is not pressed.
		if (window->GetInput().keyboard.IsKeyDown(Key::Escape))
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