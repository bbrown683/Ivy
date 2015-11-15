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

#pragma once

#include "Math.h"

namespace Jade
{
	namespace Math
	{
		struct Vector2
		{
		private:

			float x;
			float y;
			float magnitude;

		public:

			// Vector2 operator overloads.

			inline bool operator==(const Vector2 vector)
			{
				return (this->x - vector.x < Math::Epsilon) && (this->y - vector.y < Math::Epsilon) ? true : false;
			}

			inline bool operator!=(const Vector2 vector)
			{
				return !(this == &vector);
			}

			inline Vector2 operator+(const Vector2 vector)
			{
				return Vector2(this->x + vector.x, this->y + vector.y);
			}

			inline Vector2 operator-(const Vector2 vector)
			{
				return Vector2(this->x - vector.x, this->y - vector.y);
			}

			inline Vector2 operator*(const float scalar)
			{
				return Vector2(this->x * scalar, this->y * scalar);
			}

			inline Vector2 operator/(const float scalar)
			{
				return Vector2(this->x / scalar, this->y - scalar);
			}

			Vector2(float x, float y)
			{
				this->x = x;
				this->y = y;

				magnitude = Math::Sqrt(x * x + y * y);
			}

			float Distance(Vector2 target);

			void Normalize();

			void SetX(float value);
			float GetX();

			void SetY(float value);
			float GetY();
			
			float GetMagnitude();
		};
	}
}
