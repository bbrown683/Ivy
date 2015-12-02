#pragma once

#include "Graphics/Window/Window.h"
#include "Graphics/Device/GraphicsDeviceManager.h"

class Game
{
private:

	Jade::Graphics::Window* window;
	Jade::Graphics::GraphicsDeviceManager* graphics;

	int width;
	int height;
	int x;
	int y;
	string title;
	bool fullscreen;

public:

	Game(int width, int height, int x, int y, string title, bool fullscreen)
	{
		window = new Jade::Graphics::Window(width, height, x, y, title, fullscreen);

		graphics = new Jade::Graphics::GraphicsDeviceManager(window);
	}

	~Game()
	{
		delete graphics;
		delete window;
	}

	void Run();

	void Render();

	void Update();
};