#pragma once

namespace Jade
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