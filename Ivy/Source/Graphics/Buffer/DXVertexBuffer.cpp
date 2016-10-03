#include "DXVertexBuffer.h"

#ifdef IVY_PLATFORM_WINDOWS
void Ivy::Graphics::DXVertexBuffer::Bind()
{
	// MakeActive the memory stride.
	unsigned int stride = sizeof(Math::Vertex);
	unsigned int offset = 0;

	// MakeActive the vertices buffer.
	device->GetID3D11DeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	device->GetID3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Ivy::Graphics::DXVertexBuffer::Create()
{
	// Reset the state each frame.
	if (m_pVertexBuffer)
		m_pVertexBuffer.Reset();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = static_cast<unsigned int>(sizeof(Math::Vertex) * vertices.size());
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	// Pass the data to the Direct3D11 object.
	InitData.pSysMem = vertices.data();

	// Creaate vertices buffer.
	HRESULT hr = device->GetID3D11Device()->CreateBuffer(&desc, &InitData, m_pVertexBuffer.GetAddressOf());

	// We had an error creating the buffer.
	if (FAILED(hr))
		return false;

	return true;
}

std::vector<Ivy::Math::Vertex> Ivy::Graphics::DXVertexBuffer::GetVertices()
{
	return vertices;
}

void Ivy::Graphics::DXVertexBuffer::SetVertices(std::vector<Math::Vertex> vertices)
{
	this->vertices = vertices;
}

void Ivy::Graphics::DXVertexBuffer::Unbind()
{
	// Unbind buffer.
	device->GetID3D11DeviceContext()->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
}

void Ivy::Graphics::DXVertexBuffer::Draw()
{
	// Non-indexed drawing. Less efficient but simpler to implement if a mesh has no indices.
	device->GetID3D11DeviceContext()->Draw(static_cast<unsigned>(vertices.size()), 0);
}
#endif