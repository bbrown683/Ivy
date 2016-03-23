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

#include <iostream>
#include <vector>

#include "Core/Utility.h"
#include "Math/Math.h"
#include "Math/Vector3.h"

namespace Jade
{
	namespace Math
	{
		// A 4x4 structure for storing data.
		struct Matrix
		{
		private:

			float values[4][4];

		public:

			Matrix operator+(Matrix matrix) const
			{
				return Matrix(values[0][0] + matrix.values[0][0], values[0][1] + matrix.values[0][1], values[0][2] + matrix.values[0][2], values[0][3] + matrix.values[0][3], 
					values[1][0] + matrix.values[1][0], values[1][1] + matrix.values[1][1], values[1][2] + matrix.values[1][2], values[1][3] + matrix.values[1][3], 
					values[2][0] + matrix.values[2][0], values[2][1] + matrix.values[2][1], values[2][2] + matrix.values[2][2], values[2][3] + matrix.values[2][3], 
					values[3][0] + matrix.values[3][0], values[3][1] + matrix.values[3][1], values[3][2] + matrix.values[3][2], values[3][3] + matrix.values[3][3]);
			}

			Matrix operator-(Matrix matrix) const
			{
				return Matrix(values[0][0] - matrix.values[0][0], values[0][1] - matrix.values[0][1], values[0][2] - matrix.values[0][2], values[0][3] - matrix.values[0][3],
					values[1][0] - matrix.values[1][0], values[1][1] - matrix.values[1][1], values[1][2] - matrix.values[1][2], values[1][3] - matrix.values[1][3],
					values[2][0] - matrix.values[2][0], values[2][1] - matrix.values[2][1], values[2][2] - matrix.values[2][2], values[2][3] - matrix.values[2][3],
					values[3][0] - matrix.values[3][0], values[3][1] - matrix.values[3][1], values[3][2] - matrix.values[3][2], values[3][3] - matrix.values[3][3]);
			}

			Matrix operator*(Matrix matrix) const
			{
				return Matrix();
			}

			Matrix operator/(Matrix matrix) const
			{
				return Matrix();
			}

			static const Matrix Identity;
			static const Matrix Zero;
			
			// Sets all values to 0.0f by default.
			Matrix()
			{
				values[0][0] = 0.0f;
				values[0][1] = 0.0f;
				values[0][2] = 0.0f;
				values[0][3] = 0.0f;
				values[1][0] = 0.0f;
				values[1][1] = 0.0f;
				values[1][2] = 0.0f;
				values[1][3] = 0.0f;
				values[2][0] = 0.0f;
				values[2][1] = 0.0f;
				values[2][2] = 0.0f;
				values[2][3] = 0.0f;
				values[3][0] = 0.0f;
				values[3][1] = 0.0f;
				values[3][2] = 0.0f;
				values[3][3] = 0.0f;
			}

			Matrix(float m00, float m01, float m02, float m03, 
				float m10, float m11, float m12, float m13, 
				float m20, float m21, float m22, float m23, 
				float m30, float m31, float m32, float m33)
			{
				values[0][0] = m00;
				values[0][1] = m01;
				values[0][2] = m02;
				values[0][3] = m03;
				values[1][0] = m10;
				values[1][1] = m11;
				values[1][2] = m12;
				values[1][3] = m13;
				values[2][0] = m20;
				values[2][1] = m21;
				values[2][2] = m22;
				values[2][3] = m23;
				values[3][0] = m30;
				values[3][1] = m31;
				values[3][2] = m32;
				values[3][3] = m33;
			}

			Matrix Add(Matrix other) const;
			float Determinant();
			Matrix CreateLeftHandPerspectiveView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
			Matrix CreateRightHandPerspectiveView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
			Matrix Divide(Matrix other) const;
			Matrix LookAt(Vector3 eye, Vector3 at, Vector3 up);
			Matrix Multiply(Matrix other) const;
			Matrix Negate();
			Matrix RotateAlongX(float radians) const;
			Matrix RotateAlongY(float radians) const;
			Matrix RotateAlongZ(float radians) const;
			Matrix Subtract(Matrix other) const;
			Matrix Translate(float xOffset, float yOffset, float zOffset);
			Matrix Transpose();
			string ToString();
		};
	}
}
