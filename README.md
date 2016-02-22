# Jade
An Open Source C++ Game Engine inspired by [Monogame](http://www.monogame.net/). This is compiled using Visual Studio 2015 Community Edition.

# Dependencies
* DirectX - Must be using one of the following Operating Systems: Windows Vista, Windows 7, Windows 8 and Windows 10 for compatibility.
* OpenGL - This is used for non-Windows Operating Systems such as Linux or MacOSX that use the X11 or Cocoa windowing system.
* Glew - This is needed to load all modern OpenGL entry points so they can be used.
* SDL - Used to create a window, manage events, and allows us to create a device for Direct3D11 or OpenGL 4.5

# Features
Basic DirectX and OpenGL backend, allowing for use of either graphics API, which is currently chosen based on the specific Operating System in use. Will be implementing the [HLSLCrossCompiler by James Jones](https://github.com/James-Jones/HLSLCrossCompiler) to create portable shader code.

# Example Application
```c++
#include "Graphics/Window/Window.h"
#include "Graphics/Device/Device.h"

using Jade::Graphics::Window;
using Jade::Graphics::Device;

int main(int argc, char* argv[])
{
	   // Creates a basic window that can be rendered to with either graphics API.
	   std::shared_ptr<Window> window = std::make_shared<Window>(Window(1080, 720, 100, 100, "Hello World", false));

	   // Creates an OpenGL or DirectX device depending on window type.
	   std::shared_ptr<Device> device = std::make_shared<Device>(Device(window));

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
```

# Progress Mark 1
![Result](https://i.gyazo.com/1bdb3964c80b00e0a09df07e6bcc46c0.png)

# Progress Mark 2
![Result2](https://i.gyazo.com/80b709e60358b20c1ad912e354ad9b7b.png)
