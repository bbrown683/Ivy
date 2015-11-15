#include "Graphics/Window/Window.h"
#include <gl/GL.h>

Jade::Graphics::Window* window;

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
	Jade::Graphics::Event e;

	if (window->PollEvents(&e))
	{
		switch (e.GetEventType())
		{
		case Jade::Graphics::Event::EventType::Close:
				break;
		}
	}
}

int main()
{
	window = new Jade::Graphics::Window(1080, 720, 100, 100, "Jade");

	while (window->IsOpen())
	{
		Update();

		Render();
	}
}
