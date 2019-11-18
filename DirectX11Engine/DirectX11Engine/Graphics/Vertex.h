#pragma once
#include <DirectXMath.h>
class Vertex {
public:
	Vertex() : pos(0.0f, 0.0f) {}
	Vertex(float x, float y) : pos(x, y) {}
	DirectX::XMFLOAT2 pos;
};