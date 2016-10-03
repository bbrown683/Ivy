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

namespace Ivy
{
	namespace System
	{
		class Timer
		{
			float deltaTime;
			float elapsedTime;

		public:

            Timer() : deltaTime(0.0f), elapsedTime(0.0f) { }

			// Returns the time between frame refreshes.
			float GetDeltaTime() const
			{
				return deltaTime;
			}

			// Do not set this value as it is done manually...
			void SetDeltaTime(float value)
			{
				deltaTime = value;
			}

			// Returns the elapsed time of the program.
			float GetElaspedTime() const
			{
				return elapsedTime;
			}

			// Do not set this value as it is done manually...
			void SetElapsedTime(float value)
			{
				elapsedTime = value;
			}
		};
	}
}