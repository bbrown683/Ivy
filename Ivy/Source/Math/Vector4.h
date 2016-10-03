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

#include <glm/vec4.hpp>

#include "Core/Include.h"
#include "Math/Math.h"

namespace Ivy
{
	namespace Math
	{
		struct Vector4
		{
			// Vector4 operator overloads.

			bool operator==(Vector4 vector) const
			{
				return (this->values.x - vector.values.x < Math::Epsilon) &&
					(this->values.y - vector.values.y < Math::Epsilon) &&
					(this->values.z - vector.values.z < Math::Epsilon) &&
					(this->values.w - vector.values.w < Math::Epsilon) ? true : false;
			}

			bool operator!=(Vector4 vector) const
			{
				return !(*this == vector);
			}

			Vector4 operator+(Vector4 vector) const
			{
				glm::vec4 add = values + vector.values;
				return Vector4(add.x, add.y, add.z, add.w);
			}

			Vector4 operator+(float scalar) const
			{
				glm::vec4 add = values + scalar;
				return Vector4(add.x, add.y, add.z, add.w);
			}

			Vector4 operator-(Vector4 vector) const
			{
				glm::vec4 sub = values - vector.values;
				return Vector4(sub.x, sub.y, sub.z, sub.w);
			}

			Vector4 operator-(float scalar) const
			{
				glm::vec4 sub = values - scalar;
				return Vector4(sub.x, sub.y, sub.z, sub.z);
			}

			Vector4 operator*(float scalar) const
			{
				glm::vec4 mul = values * scalar;
				return Vector4(mul.x, mul.y, mul.z, mul.w);
			}

			Vector4 operator/(float scalar) const
			{
				glm::vec4 div = values / scalar;
				return Vector4(div.x, div.y, div.z, div.w);
			}

			Vector4()
			{
				values = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			}

			Vector4(float x, float y, float z)
			{
				values = glm::vec4(x, y, z, 1.0f);
			}

			Vector4(float x, float y, float z, float w)
			{
				values = glm::vec4(x, y, z, w);
			}

			void SetX(float value);
			float GetX();

			void SetY(float value);
			float GetY();

			void SetZ(float value);
			float GetZ();

			void SetW(float value);
			float GetW();

			std::string ToString() const;

		private:

			glm::vec4 values;
		};
	}
}