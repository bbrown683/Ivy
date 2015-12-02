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

namespace Jade
{
	namespace Math
	{
		// Wrapper class for using Colors in both OpenGL and DirectX without having API dependencies.
		struct Color
		{
		private:

			float red;
			float green;
			float blue;
			float alpha;

		public:

			// List of some common .NET Colors translated into their respective values for OpenGL and DirectX.
			static const Color CornflowerBlue;
			static const Color Red;
			static const Color Green;
			static const Color Blue;
			static const Color Black;
			static const Color White;

			Color(float red, float green, float blue, float alpha)
			{			
				this->red		= red;
				this->green		= green;
				this->blue		= blue;
				this->alpha		= alpha;
			}

			float GetRed() const
			{
				return red;
			}

			float GetGreen() const
			{
				return green;
			}

			float GetBlue() const
			{
				return blue;
			}

			float GetAlpha() const
			{
				return alpha;
			}
		};
	}
}