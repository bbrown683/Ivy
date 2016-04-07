/*
The MIT License (MIT)

Copyright (c) 20.0f1.0.0ff5 Ben Brown

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

#include "Matrix.h"

const Jade::Math::Matrix Jade::Math::Matrix::Identity(
	1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);
const Jade::Math::Matrix Jade::Math::Matrix::Zero(
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f);

Jade::Math::Matrix Jade::Math::Matrix::Add(Matrix other) const
{
	return *this + other;
}

Jade::Math::Matrix Jade::Math::Matrix::CreateLookAt(Vector3 eye, Vector3 at, Vector3 up)
{
	Vector3 zAxis = (at - eye).Normalize();
	Vector3 xAxis = up.Cross(zAxis).Normalize();
	Vector3 yAxis = zAxis.Cross(xAxis);

	// For a summary of how this is computed use the link below.
	// https://msdn.microsoft.com/en-us/library/bb205342(v=vs.85).aspx
	return Matrix(eye.GetX(), eye.GetY(), eye.GetZ(), 0,
		at.GetX(), at.GetY(), at.GetZ(), 0,
		up.GetX(), up.GetY(), up.GetZ(), 0,
		-xAxis.Dot(eye), -yAxis.Dot(eye), -(zAxis.Dot(eye)), 1);
}

Jade::Math::Matrix Jade::Math::Matrix::CreateOrthographicView(float width, float height, float nearPlaneDistance, float farPlaneDistance)
{
	// Handling input parameters.
	if ((nearPlaneDistance > 0 && farPlaneDistance > 0) &&
		(nearPlaneDistance < farPlaneDistance))
		// For a summary of how this is computed use the link below.
		// https://msdn.microsoft.com/en-us/library/bb205346(v=vs.85).aspx
		return Matrix(2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f / (farPlaneDistance - nearPlaneDistance), -1.0f,
			0.0f, 0.0f, -nearPlaneDistance / (farPlaneDistance - nearPlaneDistance), 0.0f);

	// return an empty matrix otherwise.
	return Matrix();
}


Jade::Math::Matrix Jade::Math::Matrix::CreatePerspectiveView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
	// Handling input parameters.
	if ((fieldOfView >= 0 && fieldOfView <= Math::Pi) &&
		(nearPlaneDistance > 0 && farPlaneDistance > 0) &&
		(nearPlaneDistance < farPlaneDistance))
		// For a summary of how this is computed use the link below.
		// https://msdn.microsoft.com/en-us/library/bb205350(v=vs.85).aspx
		return Matrix((1 / Math::Tan(fieldOfView) * 0.5f), 0.0f, 0.0f, 0.0f,
			0.0f, ((1 / Math::Tan(fieldOfView * 0.5f)) / aspectRatio), 0.0f, 0.0f,
			0.0f, 0.0f, farPlaneDistance / (farPlaneDistance - nearPlaneDistance), -1.0f,
			0.0f, 0.0f, -(nearPlaneDistance * farPlaneDistance) / (farPlaneDistance - nearPlaneDistance), 0.0f);

	// return an empty matrix otherwise.
	return Matrix();
}

float(&Jade::Math::Matrix::Data())[4][4]
{
	return values;
}

float Jade::Math::Matrix::Determinant()
{
	return 0.0f;
}

Jade::Math::Matrix Jade::Math::Matrix::Divide(Matrix other) const
{
	return *this / other;
}

Jade::Math::Matrix Jade::Math::Matrix::Multiply(Matrix other) const
{
	return *this / other;
}

Jade::Math::Matrix Jade::Math::Matrix::Negate()
{
	return Matrix(-values[0][0], -values[0][1], -values[0][2], -values[0][3],
		-values[1][0], -values[1][1], -values[1][2], -values[1][3],
		-values[2][0], -values[2][1], -values[2][2], -values[2][3],
		-values[3][0], -values[3][1], -values[3][2], -values[3][3]);
}

Jade::Math::Matrix Jade::Math::Matrix::Subtract(Matrix other) const
{
	return *this - other;
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongX(float radians)
{
	return Matrix(1, 0, 0, 0, 0, Math::Cos(radians), Math::Sin(radians), 0, 0, Math::Sin(-1.0f * radians), Math::Cos(radians), 0, 0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongY(float radians)
{
	return Matrix(Math::Cos(radians), 0, Math::Sin(-1.0f * radians), 0, 0, 1, 0, 0, Math::Sin(radians), 0, Math::Cos(radians), 0, 0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongZ(float radians) const
{
	return  Matrix(Math::Cos(radians), Math::Sin(-1.0f * radians), 0, 0, Math::Sin(radians), Math::Cos(radians), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::Transpose()
{
	return Matrix(values[0][0], values[1][0], values[2][0], values[3][0], 
		values[0][1], values[1][1], values[2][1], values[3][1], 
		values[0][2], values[1][2], values[2][2], values[3][2], 
		values[0][3], values[1][3], values[2][3], values[3][3]);
}

std::string Jade::Math::Matrix::ToString()
{
	std::string matrix = "";

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == 0)
				matrix = matrix + "[\t";
			if (k < 3)
				matrix = matrix + std::to_string(values[i][k]) + "\t";
			else if (k == 3)
				matrix = matrix + std::to_string(values[i][k]) + "\t]\n";
		}
	}

	return matrix;
}
