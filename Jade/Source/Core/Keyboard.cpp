#include "Keyboard.h"

bool Jade::Core::Keyboard::IsKeyUp(Key key)
{
	return keyState[key] == InputState::Released ? true : false;
}

bool Jade::Core::Keyboard::IsKeyDown(Key key)
{
	return keyState[key] == InputState::Pressed ? true : false;
}

std::vector<Jade::Core::Key> Jade::Core::Keyboard::GetKeysPressed()
{
	std::vector<Key> keysPressed;

	for (auto iterator = keyState.begin(); iterator != keyState.end(); ++iterator)
	{
		if (iterator->second == InputState::Pressed)
			keysPressed.push_back(iterator->first);
	}

	return keysPressed;
}

void Jade::Core::Keyboard::SetKeyState(Key key, InputState state)
{	
	// Insert or update if its state changed.
	if (keyState[key] != state)
		keyState[key] = state;
}
