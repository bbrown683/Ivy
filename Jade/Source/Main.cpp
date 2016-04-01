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

#include "System/Window/Window.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Model/Model.h"
#include "Graphics/Font/Font.h"

using namespace Jade::Core;
using namespace Jade::Input;
using namespace Jade::Graphics;
using namespace Jade::Math;
using namespace Jade::System;

int main(int argc, char* argv[])
{
	// Creates a basic window that can be rendered with either graphics API.
	Window window(1080, 720, 100, 100, "Hello World", false);

	// Creates a graphics device.
	Device device(window, GraphicsAPI::DirectX);

	// Map for holding our shaders. 
	std::map<std::string, ShaderType> shaders =
	{
		{ ".\\resources\\shaders\\vertex.cso", ShaderType::Vertex },
		{ ".\\resources\\shaders\\pixel.cso", ShaderType::Pixel },
	};

	// Create our shaders.
	Shader shader(device, shaders);

	// Create and load the model.
	Model model(device);
	model.Load(".\\resources\\models\\teapot.obj");

	Font font(".\\resources\\fonts\\consolas.ttf");

	while (window.IsOpen())
	{
		// Rendering
		device.Clear(Color::CornflowerBlue);

		// Draw the model.
		model.Draw();

		// Gets the keys pressed and prints their enumerication value that is stored as an integer.
		std::vector<Key> keysPressed = window.GetInput().keyboard.GetKeysPressed();
		for (unsigned int i = 0; i < keysPressed.size(); i++)
			std::cout << static_cast<int>(keysPressed[i]) << std::endl;
		
		if(window.GetInput().keyboard.IsKeyDown(Key::Escape))
		{
			window.Close();
		}
		else
		{
			device.Present();
			window.PollEvents();
		}
	}

	return 0;
}