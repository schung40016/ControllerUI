#include "pch.h"
#include "Triangle.h"

// Constructor
Triangle::Triangle()
{
}

// Create a instance of an equallateral triangle at a specified position.
Triangle::Triangle(DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float inp_scale, float inp_x, float inp_y)
{
	uiObj_color = colorInput;
	gObj_parentObj = &inp_parentObj;
	gObj_scale = inp_scale;
	gObj_position.x = inp_x;
	gObj_position.y = inp_y;
}

// Draw Triangle.
void Triangle::Draw(const std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& inp_batch) const 
{
	DirectX::SimpleMath::Vector2 newPos = GetPosition();
	float currScale = GetScale();

	VertexPositionColor v1(Vector3(newPos.x + 50.f * currScale, newPos.y + 18.75f * currScale, 0.f), uiObj_color);
	VertexPositionColor v2(Vector3(newPos.x + 75.f * currScale, newPos.y + 56.25f * currScale, 0.f), uiObj_color);
	VertexPositionColor v3(Vector3(newPos.x + 25.f * currScale, newPos.y + 56.25f * currScale, 0.f), uiObj_color);

	inp_batch->DrawTriangle(v1, v2, v3);
}

// Destructor
Triangle::~Triangle()
{
}
