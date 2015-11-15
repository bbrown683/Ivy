#include "Event.h"

Jade::Graphics::Event::EventType Jade::Graphics::Event::GetEventType()
{
	return type;
}

void Jade::Graphics::Event::SetEventType(Jade::Graphics::Event::EventType value)
{
	type = value;
}
