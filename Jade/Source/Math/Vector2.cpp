/*
The MIT License (MIT)

Copyright (c) 20.0f1.0f5 Ben Brown

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

#include "Vector2.h"

const Jade::Math::Vector2 Jade::Math::Vector2::Down(0.0f, -1.0f);
const Jade::Math::Vector2 Jade::Math::Vector2::Left(-1.0f, 0.0f);
const Jade::Math::Vector2 Jade::Math::Vector2::One(1.0f, 1.0f);
const Jade::Math::Vector2 Jade::Math::Vector2::Right(1.0f, 0.0f);
const Jade::Math::Vector2 Jade::Math::Vector2::Up(0.0f, 1.0f);
const Jade::Math::Vector2 Jade::Math::Vector2::Zero(0.0f, 0.0f);

float Jade::Math::Vector2::Dot(Vector2 vector) const
{
	return dot(values, vector.values);
}

float Jade::Math::Vector2::Distance(Vector2 target) const
{
	return distance(values, target.values);
}

glm::vec2 Jade::Math::Vector2::GetRawData()
{
	return values;
}

Jade::Math::Vector2 Jade::Math::Vector2::Lerp(Vector2 start, Vector2 end, float delta) const
{
	glm::vec2 lerp = glm::lerp(start.values, end.values, delta);
	return Vector2(lerp.x, lerp.y);
}

Jade::Math::Vector2 Jade::Math::Vector2::Normalize() const
{
	glm::vec2 normalized = normalize(values);
	return Vector2(normalized.x, normalized.y);
}

void Jade::Math::Vector2::SetX(float value)
{
	values.x = value;
}

float Jade::Math::Vector2::GetX() const
{
	return values.x;
}

void Jade::Math::Vector2::SetY(float value)
{
	values.y = value;
}

float Jade::Math::Vector2::GetY() const
{
	return values.y;
}

std::string Jade::Math::Vector2::ToString() const
{
	return "(" + std::to_string(values.x) + ", " +
		std::to_string(values.y) + ")";
}
