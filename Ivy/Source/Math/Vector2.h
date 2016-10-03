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

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/compatibility.hpp>

namespace Ivy
{
	namespace Math
	{
		struct Vector2
		{
			// Vector2 operator overloads.

			bool operator==(Vector2 vector) const
			{
				return (this->values.x - vector.values.x < Math::Epsilon) &&
					(this->values.y - vector.values.y < Math::Epsilon) ? true : false;
			}

			bool operator!=(Vector2 vector) const
			{
				return !(*this == vector);
			}

			Vector2 operator+(Vector2 vector) const
			{
				glm::vec2 add = values + vector.values;
				return Vector2(add.x, add.y);
			}

			Vector2 operator+(float scalar) const
			{
				glm::vec2 add = values + scalar;
				return Vector2(add.x, add.y);
			}

			Vector2 operator-(Vector2 vector) const
			{
				glm::vec2 sub = values - vector.values;
				return Vector2(sub.x, sub.y);
			}

			Vector2 operator-(float scalar) const
			{
				glm::vec2 sub = values - scalar;
				return Vector2(sub.x, sub.y);
			}

			Vector2 operator*(float scalar) const
			{
				glm::vec2 mul = values * scalar;
				return Vector2(mul.x, mul.y);
			}

			Vector2 operator/(float scalar) const
			{
				glm::vec2 div = values / scalar;
				return Vector2(div.x, div.y);
			}

			static const Vector2 Down;
			static const Vector2 Left;
			static const Vector2 One;
			static const Vector2 Right;
			static const Vector2 Up;
			static const Vector2 Zero;

			Vector2()
			{
				values = glm::vec2();
			}

			Vector2(float x, float y)
			{
				values = glm::vec2(x, y);
			}

			float Dot(Vector2 vector) const;
			float Distance(Vector2 target) const;
			glm::vec2 GetRawData();
			Vector2 Lerp(Vector2 start, Vector2 end, float delta) const;
			Vector2 Normalize() const;
			void SetX(float value);
			float GetX() const;
			void SetY(float value);
			float GetY() const;
			std::string ToString() const;

		private:

			glm::vec2 values;
		};
	}
}
