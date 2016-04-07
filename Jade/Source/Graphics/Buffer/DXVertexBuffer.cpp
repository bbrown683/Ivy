#include "DXVertexBuffer.h"

bool Jade::Graphics::DXVertexBuffer::Bind()
{
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

	// Set the memory stride.
	unsigned int stride = sizeof(Math::Vertex);
	unsigned int offset = 0;

	// Set the vertices buffer.
	device->GetID3D11DeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	// Set the primitive topology.
	device->GetID3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

bool Jade::Graphics::DXVertexBuffer::Unbind()
{
	// Unbind buffers.
	device->GetID3D11DeviceContext()->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);

	return true;
}
