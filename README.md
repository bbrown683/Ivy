# Jade
An Open Source C++ Game Engine inspired by [Monogame](http://www.monogame.net/). This is compiled using Visual Studio 2015 Community Edition.

# Supported Graphics API's
* DirectX11
* OpenGL 3.2+

# Libraries Used
* Assimp 3.0.0
* FreeImage
* stb_truetype
* [Glad](http://glad.dav1d.de/)
* OpenAL 1.1
* SDL 2.0.4
* Windows 8 SDK (DirectX11 Headers)

# Features
* Should be portable
* Very simple API
* Graphics backends
* Planned multithreading support

# Example Application
```c++
#include "System/Window/Window.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Model/Model.h"

using namespace Jade::Core;
using namespace Jade::Input;
using namespace Jade::Graphics;
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
		{ ".\\resources\\shaders\\pixel.cso", ShaderType::Pixel },
		{ ".\\resources\\shaders\\vertex.cso", ShaderType::Vertex },
	};

	// Create our shaders.
	Shader shader(device, shaders);

	// Load our model
	Model model(device, shader);
	model.Load(".\\resources\\models\\testcube.obj");

	while (window.IsOpen())
	{
		// Rendering
		device.Clear(Color::CornflowerBlue);

		// Draw the model.
		model.Draw();

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
```

Progress can be found [here](https://github.com/bbrown683/Jade/blob/master/Progress.md).
