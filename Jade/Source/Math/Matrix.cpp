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

Jade::Math::Matrix Jade::Math::Matrix::CreateLookAtLH(Vector3 eye, Vector3 at, Vector3 up)
{
	glm::mat4 lookAt = lookAtLH(eye.GetRawData(), at.GetRawData(), up.GetRawData());
	return Matrix(lookAt[0][0], lookAt[0][1], lookAt[0][2], lookAt[0][3],
		lookAt[1][0], lookAt[1][1], lookAt[1][2], lookAt[1][3],
		lookAt[2][0], lookAt[2][1], lookAt[2][2], lookAt[2][3],
		lookAt[3][0], lookAt[3][1], lookAt[3][2], lookAt[3][3]);
}

Jade::Math::Matrix Jade::Math::Matrix::CreateLookAtRH(Vector3 eye, Vector3 at, Vector3 up)
{
	glm::mat4 lookAt = lookAtRH(eye.GetRawData(), at.GetRawData(), up.GetRawData());
	return Matrix(lookAt[0][0], lookAt[0][1], lookAt[0][2], lookAt[0][3],
		lookAt[1][0], lookAt[1][1], lookAt[1][2], lookAt[1][3],
		lookAt[2][0], lookAt[2][1], lookAt[2][2], lookAt[2][3],
		lookAt[3][0], lookAt[3][1], lookAt[3][2], lookAt[3][3]);
}

Jade::Math::Matrix Jade::Math::Matrix::CreateOrthographicView(float left, float right, float top, float bottom, float nearPlaneDistance, float farPlaneDistance)
{
	glm::mat4 ortho = glm::ortho(left, right, bottom, top, nearPlaneDistance, farPlaneDistance);
	return Matrix(ortho[0][0], ortho[0][1], ortho[0][2], ortho[0][3],
		ortho[1][0], ortho[1][1], ortho[1][2], ortho[1][3],
		ortho[2][0], ortho[2][1], ortho[2][2], ortho[2][3],
		ortho[3][0], ortho[3][1], ortho[3][2], ortho[3][3]);
}

Jade::Math::Matrix Jade::Math::Matrix::CreatePerspectiveViewLH(float fieldOfView, float width, float height, float nearPlaneDistance, float farPlaneDistance)
{
	glm::mat4 perspective = glm::perspectiveFovLH(fieldOfView, width, height, nearPlaneDistance, farPlaneDistance);
	return Matrix(perspective[0][0], perspective[0][1], perspective[0][2], perspective[0][3],
		perspective[1][0], perspective[1][1], perspective[1][2], perspective[1][3],
		perspective[2][0], perspective[2][1], perspective[2][2], perspective[2][3],
		perspective[3][0], perspective[3][1], perspective[3][2], perspective[3][3]);
}

Jade::Math::Matrix Jade::Math::Matrix::CreatePerspectiveViewRH(float fieldOfView, float width, float height, float nearPlaneDistance, float farPlaneDistance)
{
	glm::mat4 perspective = glm::perspectiveFovRH(fieldOfView, width, height, nearPlaneDistance, farPlaneDistance);
	return Matrix(perspective[0][0], perspective[0][1], perspective[0][2], perspective[0][3],
		perspective[1][0], perspective[1][1], perspective[1][2], perspective[1][3],
		perspective[2][0], perspective[2][1], perspective[2][2], perspective[2][3],
		perspective[3][0], perspective[3][1], perspective[3][2], perspective[3][3]);
}

glm::mat4 Jade::Math::Matrix::GetRawData()
{
	return values;
}

float Jade::Math::Matrix::Determinant()
{
	return glm::determinant(values);
}

Jade::Math::Matrix Jade::Math::Matrix::Divide(Matrix other) const
{
	return *this / other;
}

Jade::Math::Matrix Jade::Math::Matrix::Inverse()
{
	glm::mat4 inverse = glm::inverse(values);
	return Matrix(inverse[0][0], inverse[0][1], inverse[0][2], inverse[0][3],
		inverse[1][0], inverse[1][1], inverse[1][2], inverse[1][3],
		inverse[2][0], inverse[2][1], inverse[2][2], inverse[2][3],
		inverse[3][0], inverse[3][1], inverse[3][2], inverse[3][3]);
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

Jade::Math::Matrix Jade::Math::Matrix::Translate(float xOffset, float yOffset, float zOffset)
{
	glm::mat4 translated = glm::translate(values, glm::vec3(xOffset, yOffset, zOffset));
	return Matrix(translated[0][0], translated[0][1], translated[0][2], translated[0][3],
		translated[1][0], translated[1][1], translated[1][2], translated[1][3],
		translated[2][0], translated[2][1], translated[2][2], translated[2][3],
		translated[3][0], translated[3][1], translated[3][2], translated[3][3]);
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongX(float radians)
{
	return Matrix(1, 0, 0, 0,
		0, Math::Cos(radians), Math::Sin(radians), 0,
		0, Math::Sin(-1.0f * radians), Math::Cos(radians), 0,
		0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongY(float radians)
{
	return Matrix(Math::Cos(radians), 0, Math::Sin(-1.0f * radians), 0,
		0, 1, 0, 0,
		Math::Sin(radians), 0, Math::Cos(radians), 0,
		0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongZ(float radians)
{
	return Matrix(Math::Cos(radians), Math::Sin(-1.0f * radians), 0, 0,
		Math::Sin(radians), Math::Cos(radians), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::Transpose()
{
	glm::mat4 transposed = glm::transpose(values);
	return Matrix(transposed[0][0], transposed[0][1], transposed[0][2], transposed[0][3],
		transposed[1][0], transposed[1][1], transposed[1][2], transposed[1][3],
		transposed[2][0], transposed[2][1], transposed[2][2], transposed[2][3],
		transposed[3][0], transposed[3][1], transposed[3][2], transposed[3][3]);
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
