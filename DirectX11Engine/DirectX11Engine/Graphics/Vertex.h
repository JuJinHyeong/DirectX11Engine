#pragma once
#include <DirectXMath.h>

class Vertex2D {
public:
	Vertex2D() : pos(0.0f, 0.0f, 0.0f), coord(0.0f, 0.0f) {}
	Vertex2D(float x, float y, float z, float u, float v)
		: pos(x, y, z), coord(u, v){}
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 coord;
};

class Vertex3D {
public:
	Vertex3D() : pos(0.0f, 0.0f, 0.0f), coord(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	Vertex3D(float x, float y, float z, float u, float v, float nx, float ny, float nz) 
		: pos(x, y, z), coord(u, v), normal(nx, ny, nz) {}
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 coord;
	DirectX::XMFLOAT3 normal;
};