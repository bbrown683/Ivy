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

#include "Vector4.h"

static const Ivy::Math::Vector4 One(1.0f, 1.0f, 1.0f, 1.0f);
static const Ivy::Math::Vector4 Zero(0.0f, 0.0f, 0.0f, 0.0f);

void Ivy::Math::Vector4::SetX(float value)
{
	values.x = value;
}

float Ivy::Math::Vector4::GetX()
{
	return values.x;
}

void Ivy::Math::Vector4::SetY(float value)
{
	values.y = value;
}

float Ivy::Math::Vector4::GetY()
{
	return values.y;
}

void Ivy::Math::Vector4::SetZ(float value)
{
	values.z = value;
}

float Ivy::Math::Vector4::GetZ()
{
	return values.z;
}

void Ivy::Math::Vector4::SetW(float value)
{
	values.w = value;
}

float Ivy::Math::Vector4::GetW()
{
	return values.w;
}

std::string Ivy::Math::Vector4::ToString() const
{
	return "(" + std::to_string(values.x) + ", " +
		std::to_string(values.y) + ", " +
		std::to_string(values.z) + ", " +
		std::to_string(values.w) + ")";
}
