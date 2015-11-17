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

static const Jade::Math::Vector3 Back		= Jade::Math::Vector3(0.0f, 0.0f, -1.0f);
static const Jade::Math::Vector3 Down		= Jade::Math::Vector3(0.0f, -1.0f, 0.0f);
static const Jade::Math::Vector3 Forward	= Jade::Math::Vector3(0.0f, 0.0f, 1.0f);
static const Jade::Math::Vector3 Left		= Jade::Math::Vector3(-1.0f, 0.0f, 0.0f);
static const Jade::Math::Vector3 One		= Jade::Math::Vector3(1.0f, 1.0f, 1.0f);
static const Jade::Math::Vector3 Right		= Jade::Math::Vector3(1.0f, 0.0f, 0.0f);
static const Jade::Math::Vector3 Up			= Jade::Math::Vector3(0.0f, 1.0f, 0.0f);
static const Jade::Math::Vector3 Zero		= Jade::Math::Vector3(0.0f, 0.0f, 0.0f);

void Jade::Math::Vector3::SetX(float value)
{
	this->x = value;
}

float Jade::Math::Vector3::GetX() const
{
	return this->x;
}

void Jade::Math::Vector3::SetY(float value)
{
	this->y = value;
}

float Jade::Math::Vector3::GetY() const
{
	return this->y;
}

void Jade::Math::Vector3::SetZ(float value)
{
	this->z = value;
}

float Jade::Math::Vector3::GetZ() const
{
	return this->z;
}

float Jade::Math::Vector3::GetMagnitude() const
{
	return this->magnitude;
}
