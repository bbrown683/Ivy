#pragma once

// Contains some information on preferred graphics rendering modes.
struct DeviceManager
{
	int width;
	int height;
	bool fullscreen;
	int samples;
	int stencil;
	int depth;

	bool FindDevice();
};