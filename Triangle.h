#pragma once

#include "pch.h"
#include "UIObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Triangle : public UIObject
{
private:

public:
	// Constructor
	Triangle();

	Triangle(DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float input_scale, float inp_x, float inp_y);

	// Draw Triangle.
	void Draw(const std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& inp_batch) const;

	~Triangle();
};