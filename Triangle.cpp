#include "pch.h"
#include "Triangle.h"

// Constructor
Triangle::Triangle()
{
}

// Create a instance of an equallateral triangle at a specified position.
Triangle::Triangle(DirectX::XMVECTOR colorInput, float inp_size, float inp_x, float inp_y, bool inp_show)
	: shapeColor(colorInput), size(inp_size), x(inp_x), y(inp_y), display(inp_show)
{
}

// Draw Triangle.
void Triangle::DrawTriangle(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch)
{
	VertexPositionColor v1(Vector3(x + 50.f * size, y + 18.75f * size, 0.f), Colors::LightPink);
	VertexPositionColor v2(Vector3(x + 75.f * size, y + 56.25f * size, 0.f), Colors::LightPink);
	VertexPositionColor v3(Vector3(x + 25.f * size, y + 56.25f * size, 0.f), Colors::LightPink);

	m_batch->DrawTriangle(v1, v2, v3);
}

// Getters & Setters
bool Triangle::GetDisplay()
{
	return display;
}

void Triangle::SetSize(float inp_size)
{
	size = inp_size;
}

void Triangle::SetPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Triangle::SetColor(DirectX::XMVECTOR inp_color)
{
	shapeColor = inp_color;
}

void Triangle::SetDisplay(bool inp_show)
{
	display = inp_show;
}

// Destructor
Triangle::~Triangle()
{
}
