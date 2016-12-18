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

void Ivy::Graphics::Sprite::Draw()
{
    if (blending)
        blender.SetBlendState(0x000000FF);

    // Make the shader active for this object.
    shader.MakeActive();

    // Set the world matrix for the object.
    cBuffer.SetWorldMatrix(mTranslation * mRotation * mScale);

    // Bind the vertex buffer.
    vBuffer.Bind();

    // Assign the matrix data to the buffer.
    cBuffer.UpdateMatrices();

    // Set the current texture.
    texture.MakeActive();

    // Draw the sprite with the vertex buffer.
    vBuffer.Draw();

    // Unbind vertex buffer.
    vBuffer.Unbind();

    // Unbind shader for next object.
    shader.MakeInactive();

    if (blending)
        blender.DisableBlendState();
}

void Ivy::Graphics::Sprite::Blending(bool blending)
{
    this->blending = blending;
}

bool Ivy::Graphics::Sprite::Load(std::string filename)
{
    // Generate the texture for the sprite.
    texture = Texture(device, filename, TextureType::Bitmap);
    if (texture.CreateTextureFromFile())
        return true;

    return false;
}

Ivy::Math::Vector3 Ivy::Graphics::Sprite::GetPosition()
{
    return vPosition;
}

Ivy::Math::Vector3 Ivy::Graphics::Sprite::GetRotation()
{
    return vRotation;
}

Ivy::Math::Vector3 Ivy::Graphics::Sprite::GetScale()
{
    return vScale;
}

void Ivy::Graphics::Sprite::SetPosition(Math::Vector3 position)
{
    vPosition = vPosition + position;
    mTranslation = mTranslation.Translate(vPosition.GetX(), 
        vPosition.GetY(), vPosition.GetZ()).Transpose();
}

void Ivy::Graphics::Sprite::SetRotation(Math::Vector3 rotation)
{
    vRotation = vRotation + rotation;

    // Ensure rotation values does not exceed + or - 2 Pi.
    // If this is not moderated, an overflow could eventually occur.
    if (this->vRotation.GetX() > Math::Math::TwoPi || this->vRotation.GetX() < -Math::Math::TwoPi)
        this->vRotation.SetX(Math::Helper::WrapAngle(this->vRotation.GetX()));
    if (this->vRotation.GetY() > Math::Math::TwoPi || this->vRotation.GetY() < -Math::Math::TwoPi)
        this->vRotation.SetY(Math::Helper::WrapAngle(this->vRotation.GetY()));
    if (this->vRotation.GetZ() > Math::Math::TwoPi || this->vRotation.GetZ() < -Math::Math::TwoPi)
        this->vRotation.SetZ(Math::Helper::WrapAngle(this->vRotation.GetZ()));

    mRotation = (mRotation.RotateAlongX(vRotation.GetX()) *
        mRotation.RotateAlongY(vRotation.GetY()) * 
        mRotation.RotateAlongZ(vRotation.GetZ())).Transpose();
}

void Ivy::Graphics::Sprite::SetScale(Math::Vector3 scale)
{
    vScale = vScale + scale;
    mScale = mScale.Scale(vScale).Transpose();
}
