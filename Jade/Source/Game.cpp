#include "Game.h"
#include <iostream>

void Game::Run()
{
	while(window->IsOpen())
	{
		Render();

		Update();
	}
}

void Game::Render()
{
	graphics->GetGraphicsDevice()->Clear(Jade::Math::Color::CornflowerBlue);
}

void Game::Update()
{
	Jade::Graphics::Event e;

	if (window->PollEvents(&e))
	{
		switch (e.GetEventType())
		{
		case Jade::Graphics::Event::EventType::Close:
			std::cout << "Closed" << std::endl;
			break;
		}
	}

	graphics->GetGraphicsDevice()->Present();
}
