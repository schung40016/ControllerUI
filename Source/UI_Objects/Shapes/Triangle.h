#pragma once

#include "Source/pch.h"
#include "Shape.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Triangle : public Shape
{
public:
	// Constructor
	Triangle();

	Triangle(std::string id, DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float input_scale, float inp_x, float inp_y, float inp_len, float inp_wid);

	// Draw Triangle.
	void Draw(const std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>& inp_batch) const override;

	~Triangle();
};