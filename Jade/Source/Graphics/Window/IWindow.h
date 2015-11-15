#pragma once

#include "Event.h"

// Contains some methods that we can implement across multiple platforms.
struct IWindow
{
	// Assessors and Mutators.
	virtual int GetWidth() = 0;
	virtual void SetWidth(int value) = 0;

	virtual int GetHeight() = 0;
	virtual void SetHeight(int value) = 0;

	//virtual int GetX() = 0;
	//virtual void SetX(int value) = 0;

	//virtual int GetY() = 0;
	//virtual void SetY(int value) = 0;

	//virtual void SetPosition(int x, int y) = 0;

	// General window applications.
	virtual bool IsOpen() = 0;
	virtual bool WindowEvent(Jade::Graphics::Event* e) = 0;
	virtual bool SwapWindowBuffers() = 0;
	virtual void Close() = 0;
	virtual bool InitWindow() = 0;
};