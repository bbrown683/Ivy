#include "Graphics/Window/Window.h"
#include <gl/GL.h>

#include <iostream>

using namespace Jade;

Graphics::Window* window;

// Draw then swap window buffers.
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(100.0f / 255, 149.0f / 255, 237.0f / 255, 255.0f / 255);

	window->SwapBuffers();
}

// Gather input and window events and handle them.
void Update()
{
	Graphics::Event e;

	if (window->PollEvents(&e))
	{
		switch (e.GetEventType())
		{
		case Graphics::Event::EventType::Close:
			std::cout << "Closed" << std::endl;
			break;
		}
	}
}

int main()
{
	window = new Graphics::Window(1080, 720, 100, 100, "Jade", false);

	while (window->IsOpen())
	{
		Update();

		Render();
	}
}
