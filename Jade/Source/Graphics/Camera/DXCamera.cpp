#include "DXCamera.h"

void Jade::Graphics::DXCamera::LookAt(Math::Vector3 position, Math::Vector3 target, Math::Vector3 direction)
{
	/*
	scene->world = Math::Matrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	view = view.LookAt(position, target, direction);
	projection = projection.CreateLeftHandPerspectiveView(Math::Math::PiOverTwo, device->window->GetAspectRatio(), nearPlaneDistance, farPlaneDistance);

	world = world.RotateAlongY(device->window->GetTime().GetElaspedTime());//*  DirectX::XMMatrixRotationX(device->window->GetTime().GetElaspedTime()

	scene->world = world.Transpose();
	scene->view = view.Transpose();
	scene->projection = projection.Transpose();

	// Update constant buffer.
	device->m_pImmediateContext->UpdateSubresource(device->m_pConstantBuffer, 0, nullptr, &scene, 0, 0);
	device->m_pImmediateContext->VSSetConstantBuffers(0, 1, &device->m_pConstantBuffer);
	*/
}
