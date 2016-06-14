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
#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Jade
{
	namespace Math
	{
		// A 4x4 structure for storing data.
		struct Matrix
		{
			Matrix operator+(Matrix matrix) const
			{
				glm::mat4 add = values + matrix.values;
				return Matrix(add[0][0], add[0][1], add[0][2], add[0][3],
					add[1][0], add[1][1], add[1][2], add[1][3],
					add[2][0], add[2][1], add[2][2], add[2][3],
					add[3][0], add[3][1], add[3][2], add[3][3]);
			}

			Matrix operator-(Matrix matrix) const
			{
				glm::mat4 sub = values - matrix.values;
				return Matrix(sub[0][0], sub[0][1], sub[0][2], sub[0][3],
					sub[1][0], sub[1][1], sub[1][2], sub[1][3],
					sub[2][0], sub[2][1], sub[2][2], sub[2][3],
					sub[3][0], sub[3][1], sub[3][2], sub[3][3]);
			}

			Matrix operator*(Matrix matrix) const
			{
				glm::mat4 mul = values * matrix.values;
				return Matrix(mul[0][0], mul[0][1], mul[0][2], mul[0][3],
					mul[1][0], mul[1][1], mul[1][2], mul[1][3],
					mul[2][0], mul[2][1], mul[2][2], mul[2][3],
					mul[3][0], mul[3][1], mul[3][2], mul[3][3]);
			}

			Matrix operator/(Matrix matrix) const
			{
				glm::mat4 div = values / matrix.values;
				return Matrix(div[0][0], div[0][1], div[0][2], div[0][3],
					div[1][0], div[1][1], div[1][2], div[1][3],
					div[2][0], div[2][1], div[2][2], div[2][3],
					div[3][0], div[3][1], div[3][2], div[3][3]);
			}

			static const Matrix Identity;
			static const Matrix Zero;

			// Creates an identity matrix.
			Matrix()
			{
				values = Identity.values;
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

			//! Adds two matrices and returns a matrix as a result.
			Matrix Add(Matrix other) const;
			//! Returns a left-handed matrix with the camera vectors.
			static Matrix CreateLookAtLH(Vector3 eye, Vector3 at, Vector3 up);
			//! Returns a right-handed matrix with the camera vectors.
			static Matrix CreateLookAtRH(Vector3 eye, Vector3 at, Vector3 up);
			//! Returns a matrix that is of an Orthographic view.
			static Matrix CreateOrthographicView(float left, float right, float top, float bottom, float nearPlaneDistance, float farPlaneDistance);
			//! Returns a left-handed matrix that is of a Perspective view.
			static Matrix CreatePerspectiveViewLH(float fieldOfView, float width, float height, float nearPlaneDistance, float farPlaneDistance);
			//! Returns a right-handed matrix that is of a Perspective view.
			static Matrix CreatePerspectiveViewRH(float fieldOfView, float width, float height, float nearPlaneDistance, float farPlaneDistance);
			//! Returns a reference to the raw data contained within the matrix.
			glm::mat4 GetRawData();
			//! Returns the determinant of the matrix.
			float Determinant();
			//! Divides two matrices and returns a matrix as a result.
			Matrix Divide(Matrix other) const;
			//! Returns a matrix that is the inverse.
			Matrix Inverse();
			//! Multiplies two matrices and returns a matrix as a result.
			Matrix Multiply(Matrix other) const;
			//! Returns a matrix with the values negated.
			Matrix Negate();
			//! Rotates the matrix along the x-axis by a specified amount in radians.
			static Matrix RotateAlongX(float radians);
			//! Rotates the matrix along the y - axis by a specified amount in radians.
			static Matrix RotateAlongY(float radians);
			//! Rotates the matrix along the z - axis by a specified amount in radians.
			static Matrix RotateAlongZ(float radians);
			//! Scales a matrix.
			Matrix Scale(Vector2 scale);
			Matrix Scale(Vector3 scale);
			//! Subtracts two matrices and returns a matrix as a result.
			Matrix Subtract(Matrix other) const;
			//! Returns a matrix that is translated by the specified offsets.
			Matrix Translate(float xOffset, float yOffset, float zOffset);
			//! Returns a matrix where the rows are columns and the columns are rows.
			Matrix Transpose();
			//! Returns a string representation of the matrix.
			std::string ToString();

		private:

			glm::mat4 values;
		};
	}
}
