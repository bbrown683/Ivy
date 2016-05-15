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

#include "Core/Utility.h"
#include "Math/Math.h"

namespace Jade
{
	namespace Math
	{
		struct Vector4
		{
			float x;
			float y;
			float z;
			float w;
			float magnitude;

		public:

			// Vector4 operator overloads.

			bool operator==(const Vector4 vector)
			{
				return (this->x - vector.x < Math::Epsilon) && (this->y - vector.y < Math::Epsilon) && (this->z - vector.z < Math::Epsilon) && (this->w - vector.w < Math::Epsilon) ? true : false;
			}

			bool operator!=(const Vector4 vector)
			{
				return !(this == &vector);
			}

			Vector4 operator+(const Vector4 vector)
			{
				return Vector4(this->x + vector.x, this->y + vector.y, this->z + vector.z, this->w + vector.w);
			}

			Vector4 operator-(const Vector4 vector)
			{
				return Vector4(this->x - vector.x, this->y - vector.y, this->z - vector.z, this->w - vector.w);
			}

			Vector4 operator*(const float scalar)
			{
				return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
			}

			Vector4 operator/(const float scalar)
			{
				return Vector4(this->x / scalar, this->y - scalar, this->z / scalar, this->w / scalar);
			}

			Vector4(float x, float y, float z, float w)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;

				magnitude = Math::Sqrt(x * x + y * y + z * z + w * w);
			}

			float Distance(Vector4 target);

			void Normalize();

			void SetX(float value);
			float GetX();

			void SetY(float value);
			float GetY();

			void SetZ(float value);
			float GetZ();

			void SetW(float value);
			float GetW();

			float GetMagnitude();
		};
	}
}