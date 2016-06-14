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

#include "Core/Include.h"
#include "Math/Math.h"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/compatibility.hpp>

namespace Jade
{
	namespace Math
	{
		struct Vector3
		{
			// Vector3 operator overloads.

			bool operator==(Vector3 vector) const
			{
				return (this->values.x - vector.values.x < Math::Epsilon) &&
					(this->values.y - vector.values.y < Math::Epsilon) &&
					(this->values.z - vector.values.z < Math::Epsilon) ? true : false;
			}

			bool operator!=(Vector3 vector) const
			{
				return !(*this == vector);
			}

			Vector3 operator+(Vector3 vector) const
			{
				glm::vec3 add = values + vector.values;
				return Vector3(add.x, add.y, add.z);
			}

			Vector3 operator+(float scalar) const
			{
				glm::vec3 add = values + scalar;
				return Vector3(add.x, add.y, add.z);
			}

			Vector3 operator-(Vector3 vector) const
			{
				glm::vec3 sub = values - vector.values;
				return Vector3(sub.x, sub.y, sub.z);
			}

			Vector3 operator-(float scalar) const
			{
				glm::vec3 sub = values - scalar;
				return Vector3(sub.x, sub.y, sub.z);
			}

			Vector3 operator*(float scalar) const
			{
				glm::vec3 mul = values * scalar;
				return Vector3(mul.x, mul.y, mul.z);
			}

			Vector3 operator/(float scalar) const
			{
				glm::vec3 div = values / scalar;
				return Vector3(div.x, div.y, div.z);
			}

			static const Vector3 Back;
			static const Vector3 Down;
			static const Vector3 Forward;
			static const Vector3 Left;
			static const Vector3 One;
			static const Vector3 Right;
			static const Vector3 Up;
			static const Vector3 Zero;

			Vector3()
			{
				values = glm::vec3();
			}

			Vector3(float x, float y, float z)
			{
				values = glm::vec3(x, y, z);
			}

			Vector3 Cross(Vector3 vector) const;
			float Dot(Vector3 vector) const;
			float Distance(Vector3 target) const;
			glm::vec3 GetRawData();
			Vector3 Lerp(Vector3 start, Vector3 end, float delta) const;
			Vector3 Normalize() const;
			void SetX(float value);
			float GetX() const;
			void SetY(float value);
			float GetY() const;
			void SetZ(float value);
			float GetZ() const;
			std::string ToString() const;

		private:

			glm::vec3 values;
		};
	}
}