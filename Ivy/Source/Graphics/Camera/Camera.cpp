#include "Camera.h"

Ivy::Math::Vector3 Ivy::Graphics::Camera::GetCameraPosition() const
{
    return position;
}

void Ivy::Graphics::Camera::SetCameraPosition(Math::Vector3 position)
{
    this->position = position;
    std::cout << "Camera Position: " << position.ToString() << std::endl;
    // Update constant buffer.
    cBuffer.SetViewMatrix(Math::Matrix::CreateLookAtLH(this->position, target, Math::Vector3::Up).Transpose());
    cBuffer.UpdateMatrices();
}

Ivy::Math::Vector3 Ivy::Graphics::Camera::GetTargetPosition() const
{
    return target;
}

void Ivy::Graphics::Camera::SetTargetPosition(Math::Vector3 position)
{
    this->target = position;

    // Update constant buffer.
    cBuffer.SetViewMatrix(Math::Matrix::CreateLookAtLH(this->position, target, Math::Vector3::Up).Transpose());
    cBuffer.UpdateMatrices();
}

void Ivy::Graphics::Camera::Update()
{
    if (device.GetWindow().GetRenderViewportNeedsResize())
    {
        device.AdjustViewport();
        device.GetWindow().SetRenderViewportNeedsResize(false);

        cBuffer.SetProjectionMatrix(Math::Matrix::CreatePerspectiveViewLH(
            Math::Math::PiOverTwo, static_cast<float>(device.GetWindow().GetWidth()),
            static_cast<float>(device.GetWindow().GetHeight()), 0.1f, 1000.0f).Transpose());

        cBuffer.UpdateMatrices();

        std::cout << "Camera and viewport was adjusted." << std::endl;
    }
}
