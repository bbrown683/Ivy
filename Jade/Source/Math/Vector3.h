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
		struct Vector3
		{
		private:

			float x;
			float y;
			float z;
			float magnitude;

		public:

			// Vector3 operator overloads.

			inline bool operator==(Vector3 vector) const
			{
				return (this->x - vector.x < Math::Epsilon) && (this->y - vector.y < Math::Epsilon) && (this->z - vector.z < Math::Epsilon) ? true : false;
			}

			inline bool operator!=(Vector3 vector) const
			{
				return !(this == &vector);
			}

			inline Vector3 operator+(Vector3 vector) const
			{
				return Vector3(this->x + vector.x, this->y + vector.y, this->z + vector.z);
			}

			inline Vector3 operator-(Vector3 vector) const
			{
				return Vector3(this->x - vector.x, this->y - vector.y, this->z - vector.z);
			}

			inline Vector3 operator*(float scalar) const
			{
				return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
			}

			inline Vector3 operator/(float scalar) const
			{
				return Vector3(this->x / scalar, this->y - scalar, this->z / scalar);
			}

			Vector3(float x, float y, float z)
			{
				this->x = x;
				this->y = y;
				this->z = z;

				magnitude = Math::Sqrt(x * x + y * y + z * z);
			}

			Vector3 Cross(Vector3 vector) const;

			Vector3 Dot(Vector3 vector) const;

			float Distance(Vector3 target) const;

			Vector3 Lerp(Vector3 start, Vector3 end, float delta) const;

			void Normalize();

			void SetX(float value);
			float GetX() const;

			void SetY(float value);
			float GetY() const;

			void SetZ(float value);
			float GetZ() const;

			float GetMagnitude() const;
		};
	}
}