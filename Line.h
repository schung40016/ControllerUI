#pragma once

#include "./pch.h"
#include "IDirXObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Line : public IDirXObject
{
private:
	DirectX::XMVECTOR shapeColor = DirectX::Colors::Black;
	DirectX::SimpleMath::Vector2 point2 = { 0.f, 0.f }; // 2nd point.
	float lineSizeMultiplier = 30.f;
public:
	Line();

	Line(DirectX::XMVECTOR inp_shapeColor, IDirXObject& inp_parentObj, float inp_offsetX, float inp_offsetY, float inp_scale);

	Line(DirectX::XMVECTOR inp_shapeColor, float v1x, float v1y, float v2x, float v2y, float inp_scale);

	void DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch);

	// Getters & Setters
	DirectX::SimpleMath::Vector2 GetPoint2();

	void SetPoint2(float v2x, float v2y);
};
