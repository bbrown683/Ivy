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

#include "Sprite.h"

void Jade::Graphics::Sprite::Draw()
{
	// Make the shader active for this object.
	shader.MakeActive();

	// MakeActive the world matrix for the object.
	cBuffer.SetWorldMatrix(mTranslation * mRotation * mScale);

	// Bind the vertex buffer.
	vBuffer.Bind();

	// Assign the matrix data to the buffer.
	cBuffer.UpdateMatrices();

	// MakeActive current texture.
	texture.MakeActive();

	// Draw the sprite with the vertex buffer.
	vBuffer.Draw();

	// Unbind vertex buffer.
	vBuffer.Unbind();

	// Unbind shader for next object.
	shader.MakeInactive();
}

bool Jade::Graphics::Sprite::Load(std::string filename)
{
	// Generate the texture for the sprite.
	texture = Texture(device, filename, TextureType::Bitmap);
	if (texture.CreateTextureFromFile())
		return true;

	return false;
}

Jade::Math::Vector2 Jade::Graphics::Sprite::GetPosition()
{
	return vPosition;
}

Jade::Math::Vector2 Jade::Graphics::Sprite::GetRotation()
{
	return vRotation;
}

Jade::Math::Vector2 Jade::Graphics::Sprite::GetScale()
{
	return vScale;
}

void Jade::Graphics::Sprite::SetPosition(Math::Vector2 position)
{
	vPosition = vPosition + position;
	mTranslation = mTranslation.Translate(vPosition.GetX(), 
		vPosition.GetY(), 0.0f).Transpose();
}

void Jade::Graphics::Sprite::SetRotation(Math::Vector2 rotation)
{
	vRotation = vRotation = rotation;
	mRotation = mRotation.RotateAlongX(vRotation.GetX()) *
		mRotation.RotateAlongY(vRotation.GetY()).Transpose();
}

void Jade::Graphics::Sprite::SetScale(Math::Vector2 scale)
{
	vScale = vScale + scale;
	mScale = mScale.Scale(vScale).Transpose();
}
