#pragma once
#include <DirectXMath.h>
class Vertex {
public:
	Vertex() : pos(0.0f, 0.0f), coord(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f) {}
	Vertex(float x, float y, float r, float g, float b) : pos(x, y), coord(0.0f, 0.0f), color(r, g, b) {}
	Vertex(float x, float y, float u, float v) : pos(x, y), coord(u, v), color(0.0f, 0.0f, 0.0f) {}
	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT2 coord;
	DirectX::XMFLOAT3 color;
};