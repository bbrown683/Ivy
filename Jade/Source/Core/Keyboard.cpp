#include "Keyboard.h"

bool Jade::Core::Keyboard::IsKeyUp(Key key)
{
	return keyState[key] == InputState::Released ? true : false;
}

bool Jade::Core::Keyboard::IsKeyDown(Key key)
{
	return keyState[key] == InputState::Pressed ? true : false;
}

void Jade::Core::Keyboard::SetKeyState(Key key, InputState state)
{	
	// Insert or update if its state changed.
	if (keyState[key] != state)
		keyState[key] = state;
}
