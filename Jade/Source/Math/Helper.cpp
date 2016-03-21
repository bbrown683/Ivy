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

#include "Helper.h"

float Jade::Math::Helper::FastInvSqrt(float x)
{
	// Entire algorithm is prettied up using modern C++ features to remove compiler warnings.
	float xhalf = 0.5f * x;
	int i = *reinterpret_cast<int*>(&x);
	i = static_cast<int>(0x5f375a86 - (i >> 1));
	x = *reinterpret_cast<float*>(&i);
	x = x * (1.5f - xhalf * x * x);
	return x;
}

float Jade::Math::Helper::WrapAngle(float angle)
{
	// Go ahead and initialize our reducedAngle.
	float reducedAngle = 0.0f;

	// How many rotations an angle has can be determined by the times 
	// in which it divides by 360 Degrees.
	float timesToDivide = angle / (Math::TwoPi);

	// Positive Angle > 360
	if (timesToDivide > 1)
	{
		for (int i = 0; i < timesToDivide; i++)
		{
			reducedAngle = angle - (Math::TwoPi);
		}

		return reducedAngle;
	}
	// Negative Angle < -360
	else if (timesToDivide < -1)
	{
		for (int i = 0; i > timesToDivide; i--)
		{
			reducedAngle = angle + (Math::TwoPi);
		}

		return reducedAngle;
	}
	// Already reduced if it does not meet above conditions.
	else
	{
		return angle;
	}
}
