#pragma once

#include "pch.h"
#include "UIObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Line : public UIObject
{
private:
	DirectX::XMVECTOR shapeColor = DirectX::Colors::Black;
	DirectX::SimpleMath::Vector2 point1 = { 0.f, 0.f };
	DirectX::SimpleMath::Vector2 point2 = { 0.f, 0.f }; // 2nd point.
	float lineSizeMultiplier = 30.f;
public:
	Line();

	Line(std::string id, DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, DirectX::SimpleMath::Vector2 inp_pt2, float inp_scale, bool inp_isStatic = false);

	Line(std::string id, DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, DirectX::SimpleMath::Vector2 inp_pt1, DirectX::SimpleMath::Vector2 inp_pt2, float inp_scale, bool inp_isStatic = false);

	void DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch, const DirectX::SimpleMath::Vector2& camOffset) const;

	// Getters & Setters
	DirectX::SimpleMath::Vector2 GetPoint2();

	DirectX::SimpleMath::Vector2 GetDimensions() const override;

	void SetPoint2(float v2x, float v2y);
};
