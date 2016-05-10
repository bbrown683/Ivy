# Jade
An Open Source C++ Game Engine inspired by [Monogame](http://www.monogame.net/). This is compiled using Visual Studio 2015 Community Edition.

# Supported Graphics API's
* DirectX11 (About to be replaced with OpenGL overhaul. This will ensure the engine is cross platform.)
* OpenGL 3.2+

# Libraries Linked Against
* Assimp 3.0.0
* stb_image
* stb_truetype
* Glew 1.13.0 (Will write our own OpenGL entry point loader.)
* OpenAL 1.1
* SDL 2.0.4 (About to be replaced with Window system overhaul.)
* Windows 8 SDK (Will be removed along with DirectX11 support.)

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
	Model model(device);
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

# Progress Mark 1
![Result](https://i.gyazo.com/1bdb3964c80b00e0a09df07e6bcc46c0.png)

# Progress Mark 2
![Result2](https://i.gyazo.com/80b709e60358b20c1ad912e354ad9b7b.png)

# Progress Mark 3
![Result3](https://i.gyazo.com/72abf317dcee2554e874d5877ddc60a2.png)

# Progress Mark 4
![Result4](https://i.gyazo.com/bd5fdb66bca5d595ddbabbdb9d92b4aa.png)
