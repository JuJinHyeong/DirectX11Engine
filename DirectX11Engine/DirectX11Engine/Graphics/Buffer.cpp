#include "Buffer.h"

ID3D11Buffer* Buffer::Get()
{
	return mBuffer.Get();
}

ID3D11Buffer* const* Buffer::GetAddressOf()
{
	return mBuffer.GetAddressOf();
}

UINT Buffer::GetOffset()
{
	return mOffset;
}

UINT* Buffer::GetOffsetPointer()
{
	return &mOffset;
}
