#include "Keyboard.h"

bool Jade::Input::Keyboard::IsKeyUp(Key key)
{
	return keyState[key] == InputState::Released ? true : false;
}

bool Jade::Input::Keyboard::IsKeyDown(Key key)
{
	return keyState[key] == InputState::Pressed ? true : false;
}

std::vector<Jade::Input::Key> Jade::Input::Keyboard::GetKeysPressed()
{
	std::vector<Key> keysPressed;

	for (auto iterator = keyState.begin(); iterator != keyState.end(); ++iterator)
	{
		if (iterator->second == InputState::Pressed)
			keysPressed.push_back(iterator->first);
	}

	return keysPressed;
}

void Jade::Input::Keyboard::SetKeyState(Key key, InputState state)
{	
	// Insert or update if its state changed.
	if (keyState[key] != state)
		keyState[key] = state;
}
