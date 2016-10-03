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

#define NOMINMAX
#include <algorithm>

namespace Ivy
{
	namespace Math
	{
		class Math
		{
		public:

			// Represents the ratio of the circumference of a circle to its diameter, specified by the constant, ?.
			static const float Pi;
			// Represents the value of 2?.
			static const float TwoPi;
			// Represents the value of ? / 2.
			static const float PiOverTwo;
			// Represents the natural logarithmic base, specified by the constant, e.
			static const float E;
			// Represents the margin of error between two floating point numbers for comparisons.
			static const float Epsilon;
			// The conversion factor for going from degrees to radians.
			static const float Deg2Rad;
			// The conversion factor for going from radians to degrees.
			static const float Rad2Deg;  

			static float Min(float x, float y);

			static float Max(float x, float y);

			static float Sqrt(float x);

			static float InvSqrt(float x);

			static float ASin(float a);

			static float Sin(float a);

			static float ACos(float a);

			static float Cos(float a);

			static float ATan(float a);

			static float Tan(float a);

			static float Pow(float x, float y);

			static float Exp(float x);

			static float Log(float x);

			static float Log10(float x);

			static float Abs(float x);

			static float Remainder(float x, float y);

			static float Round(float x);

			static int Random();

			static float Floor(float x);

			static float Ceiling(float x);

			static bool IsNan(float x);
		};
	}
}