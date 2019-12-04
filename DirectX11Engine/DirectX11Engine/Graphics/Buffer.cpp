#include "Buffer.h"

ID3D11Buffer* Buffer::Get()
{
	return m_buffer.Get();
}

ID3D11Buffer* const* Buffer::GetAddressOf()
{
	return m_buffer.GetAddressOf();
}

UINT Buffer::GetOffset()
{
	return m_offset;
}

UINT* Buffer::GetOffsetPointer()
{
	return &m_offset;
}
