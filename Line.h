#pragma once

#include "./pch.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Line
{
private:
	DirectX::XMVECTOR shapeColor = DirectX::Colors::Black;
	DirectX::SimpleMath::Vector2 v1 = { 0.f, 0.f }; // Origin
	DirectX::SimpleMath::Vector2 v2 = { 1.f, 1.f }; // 2nd point.
public:
	Line();

	Line(DirectX::XMVECTOR inp_shapeColor, float v1x, float v1y, float v2x, float v2y);

	void DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch);

	// Getters & Setters
	DirectX::XMVECTOR GetColor();

	DirectX::SimpleMath::Vector2 GetVec1();

	DirectX::SimpleMath::Vector2 GetVec2();

	void SetColor(DirectX::XMVECTOR inp_shapeColor);

	void SetVec1(float v1x, float v1y);

	void SetVec2(float v2x, float v2y);
};
