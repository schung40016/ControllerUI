#include "pch.h"
#include "Triangle.h"

// Constructor
Triangle::Triangle()
{
}

// Create a instance of an equallateral triangle at a specified position.
Triangle::Triangle(DirectX::XMVECTOR colorInput, IDirXObject& inp_parentObj, float inp_scale, float inp_x, float inp_y, float offsetX = 0, 
	float offsetY = 0)
{
	m_color = colorInput;
	m_parentObj = &inp_parentObj;
	m_scale = inp_scale;
	m_position.x = inp_x;
	m_position.y = inp_y;
	m_offsetPos.x = offsetX;
	m_offsetPos.y = offsetY;
}

// Draw Triangle.
void Triangle::DrawTriangle(const std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch)
{
	VertexPositionColor v1(Vector3(m_position.x + 50.f * m_scale, m_position.y + 18.75f * m_scale, 0.f), m_color);
	VertexPositionColor v2(Vector3(m_position.x + 75.f * m_scale, m_position.y + 56.25f * m_scale, 0.f), m_color);
	VertexPositionColor v3(Vector3(m_position.x + 25.f * m_scale, m_position.y + 56.25f * m_scale, 0.f), m_color);

	m_batch->DrawTriangle(v1, v2, v3);
}

// Getters & Setters
bool Triangle::GetDisplay()
{
	return display;
}

void Triangle::SetSize(float inp_scale)
{
	m_scale = inp_scale;
}

void Triangle::SetDisplay(bool inp_show)
{
	display = inp_show;
}

// Destructor
Triangle::~Triangle()
{
}
