# Jade
An Open Source C++ Game Development Framework inspired by [Monogame](http://www.monogame.net/).

# Supported Graphics API's
* DirectX11
* OpenGL 3.2

# Libraries Used
* Assimp 3.0.0
* FreeImage
* FreeType
* [Glad](http://glad.dav1d.de/)
* GLM (OpenGL Mathematics)
* OpenAL 1.1
* Windows 7 or 8.1 SDK (DirectX11 and OpenGL Headers for Windows Development)

The following except the Windows 8 SDK is provided for out of the box compilation on x86 and x64 machines using Visual Studio 2015 Community Edition.

# Possible Implementations
* Shader interoperability with the Cg Shading Language. While its latest release was around 4 years ago, it still has support for both DirectX 11.0 and OpenGL 3. This would make it seamless to integrate into the engine allowing one to write only one set of shader code.

# Features
* Written for portability. 
* Very simple API.
* Graphics backends for OpenGL and DirectX. Vulkan is possible as well, but my card currently does not have support by AMD.
* Planned multithreading support for asset loading.

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
