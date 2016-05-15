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

#include <Graphics/Device/Device.h>
#include <Graphics/Rasterizer/DXRasterizer.h>
#include <Graphics/Rasterizer/GLRasterizer.h>
#include <Graphics/Rasterizer/IRasterizer.h>
#include <Graphics/Rasterizer/RasterizerFactory.h>

namespace Jade
{
	namespace Graphics
	{
		/* \brief 
		 *  
		 */
		class Rasterizer
		{
			Device device;
			std::shared_ptr<IRasterizer> rasterizer;

		public:

			Rasterizer(Device device)
			{
				this->device = device;

				rasterizer = RasterizerFactory::Generate<IRasterizer>(device);
			}

			/*! \brief Sets the rasterizer state to the specified cull and fill mode.
			* @param[in] cullMode Represents the faces that will be hidden from view when rendering. Front, Back, and None are accepted values here. 
			* @param[in] fillMode Represents how the faces will be rendered. Solid and Wireframe are accepted values here.
			*/
			bool SetRasterizerState(CullMode cullMode, FillMode fillMode, WindMode windMode) const
			{
				return rasterizer->SetRasterizerState(cullMode, fillMode, windMode);
			}

			/*! \brief Returns the current cull mode. Return values can only be None, Front, or Back. */
			CullMode GetCullMode() const
			{
				return rasterizer->GetCullMode();
			}

			/*! \brief Returns the current fill mode. Return values can only be Wireframe or Solid. */
			FillMode GetFillMode() const
			{
				return rasterizer->GetFillMode();
			}

			/*! \brief Returns the current wind mode. Return value can only be Clockwise or CounterClockwise */
			WindMode GetWindMode() const
			{
				return rasterizer->GetWindMode();
			}
		};
	}
}
