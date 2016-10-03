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

#include "Vector3.h"

const Ivy::Math::Vector3 Ivy::Math::Vector3::Back(0.0f, 0.0f, -1.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::Down(0.0f, -1.0f, 0.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::Forward(0.0f, 0.0f, 1.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::Left(-1.0f, 0.0f, 0.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::One(1.0f, 1.0f, 1.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::Right(1.0f, 0.0f, 0.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::Up(0.0f, 1.0f, 0.0f);
const Ivy::Math::Vector3 Ivy::Math::Vector3::Zero(0.0f, 0.0f, 0.0f);

Ivy::Math::Vector3 Ivy::Math::Vector3::Cross(Vector3 vector) const
{
	glm::vec3 cross = glm::cross(values, vector.values);
	return Vector3(cross.x, cross.y, cross.z);
}

float Ivy::Math::Vector3::Dot(Vector3 vector) const
{
	return dot(values, vector.values);
}

float Ivy::Math::Vector3::Distance(Vector3 target) const
{
	return distance(values, target.values);
}

glm::vec3 Ivy::Math::Vector3::GetRawData()
{
	return values;
}

Ivy::Math::Vector3 Ivy::Math::Vector3::Lerp(Vector3 start, Vector3 end, float delta) const
{
	glm::vec3 lerp = glm::lerp(start.values, end.values, delta);
	return Vector3(lerp.x, lerp.y, lerp.z);
}

Ivy::Math::Vector3 Ivy::Math::Vector3::Normalize() const
{
	glm::vec3 normalized = normalize(values);
	return Vector3(normalized.x, normalized.y, normalized.z);
}

void Ivy::Math::Vector3::SetX(float value)
{
	values.x = value;
}

float Ivy::Math::Vector3::GetX() const
{
	return values.x;
}

void Ivy::Math::Vector3::SetY(float value)
{
	values.y = value;
}

float Ivy::Math::Vector3::GetY() const
{
	return values.y;
}

void Ivy::Math::Vector3::SetZ(float value)
{
	values.z = value;
}

float Ivy::Math::Vector3::GetZ() const
{
	return values.z;
}

std::string Ivy::Math::Vector3::ToString() const
{
	return "(" + std::to_string(values.x) + ", " +
		std::to_string(values.y) + ", " +
		std::to_string(values.z) + ")";
}
