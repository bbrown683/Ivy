#pragma once

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

#include "Graphics/Window/Window.h"
#include "Graphics/Device/Device.h"

class Game
{
private:

	std::shared_ptr<Jade::Graphics::Window> window;
	std::shared_ptr<Jade::Graphics::Device> device;

	int width;
	int height;
	int x;
	int y;
	string title;
	bool fullscreen;

public:

	Game(int width, int height, int x, int y, string title, bool fullscreen)
	{
		window = std::make_shared<Jade::Graphics::Window>(Jade::Graphics::Window(width, height, x, y, title, fullscreen));

		device = std::make_shared<Jade::Graphics::Device>(Jade::Graphics::Device(window));
	}

	void Run();

	void Render();

	void Update();
};