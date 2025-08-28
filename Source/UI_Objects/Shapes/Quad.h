#pragma once

#include "Shape.h"

class Quad : public Shape
{
public:
	// Constructor
	Quad();

	Quad(std::string id, DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float input_scale, float inp_x, float inp_y, float inp_len, float inp_wid, bool inp_display, bool inp_isStatic = false);

	// Draw square.
	void Draw(const std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>& inp_batch, const DirectX::SimpleMath::Vector2& camOffset) const override;

	~Quad();
};