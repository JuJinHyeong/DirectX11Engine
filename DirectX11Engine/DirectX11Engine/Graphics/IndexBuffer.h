#pragma once
#include "Buffer.h"

class IndexBuffer : public Buffer {
public:
	bool Initialize(ID3D11Device* device, UINT indices[], UINT count);
	UINT GetIndexCount();
private:
	UINT mIndexCount = 0;
};