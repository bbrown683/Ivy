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

Jade::Math::Matrix Jade::Math::Matrix::Subtract(Matrix other) const
{
	return *this - other;
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongX(float radians) const
{
	return Matrix(1, 0, 0, 0, 0, Math::Cos(radians), Math::Sin(radians), 0, 0, Math::Sin(-1.0f * radians), Math::Cos(radians), 0, 0, 0, 0, 1);
}

Jade::Math::Matrix Jade::Math::Matrix::RotateAlongY(float radians) const
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

string Jade::Math::Matrix::ToString()
{
	string matrix = "";

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
