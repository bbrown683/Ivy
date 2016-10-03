#pragma once

namespace Ivy
{
	namespace Graphics
	{
		enum class DrawType
		{
			// Draws based on vertices.
			Default,
			// Draws based on indices.
			Indexed,
			// Instanced drawing.
			Instanced,
		};
	}
}