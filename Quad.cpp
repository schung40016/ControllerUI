#pragma once

#include "pch.h"
#include "Quad.h"

// Constructor
Quad::Quad()
{
}

// Create a instance of an equallateral triangle at a specified position.
Quad::Quad(DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float inp_scale, float inp_x, float inp_y, float inp_len, float inp_wid, bool inp_display)
{
	SetColor(colorInput);
	SetParent(inp_parentObj);
	SetScale(inp_scale);
	SetPosition({ inp_x, inp_y });
	SetLength(inp_len);
	SetWidth(inp_wid);
	SetDisplay(inp_display);
}

// Draw Triangle.
void Quad::Draw(const std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>& inp_batch) const
{
	if (GetDisplay() == false)
	{
		return;
	}

	DirectX::SimpleMath::Vector2 newPos = GetPosition();
	float currScale = GetScale();

	float calcLen = GetLength() / 2.0f;
	float calcWid = GetWidth() / 2.0f;

	DirectX::XMVECTOR currColor = GetColor();

	DirectX::VertexPositionColor v1(DirectX::SimpleMath::Vector3(newPos.x + calcLen * currScale, newPos.y - calcWid * currScale, 0.f), currColor);
	DirectX::VertexPositionColor v2(DirectX::SimpleMath::Vector3(newPos.x + calcLen * currScale, newPos.y + calcWid * currScale, 0.f), currColor);
	DirectX::VertexPositionColor v3(DirectX::SimpleMath::Vector3(newPos.x - calcLen * currScale, newPos.y + calcWid * currScale, 0.f), currColor);
	DirectX::VertexPositionColor v4(DirectX::SimpleMath::Vector3(newPos.x - calcLen * currScale, newPos.y - calcWid * currScale, 0.f), currColor);

	inp_batch->DrawQuad(v1, v2, v3, v4);
}

// Destructor
Quad::~Quad()
{
}
