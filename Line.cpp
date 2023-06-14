#include "pch.h"
#include "Line.h"

Line::Line()
{
}

Line::Line(DirectX::XMVECTOR inp_shapeColor, float v1x, float v1y, float v2x, float v2y)
	: shapeColor(inp_shapeColor)
{
    v1 = { v1x, v1y };
    v2 = { v2x, v2y };
}

void Line::DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch)
{
    float calcX = v2.x * 30.f + v1.x;
    float calcY = v2.y * -30.f + v1.y;

    DirectX::DX12::VertexPositionColor vec1(Vector3(v1.x, v1.y, 0.f), shapeColor);
    DirectX::DX12::VertexPositionColor vec2(Vector3(calcX, calcY, 0.f), shapeColor);
    m_batch->DrawLine(vec1, vec2);
}

// Getters & Setters
DirectX::XMVECTOR Line::GetColor()
{
    return shapeColor;
}

DirectX::SimpleMath::Vector2 Line::GetVec1()
{
    return v1;
}

DirectX::SimpleMath::Vector2 Line::GetVec2()
{
    return v2;
}

void Line::SetColor(DirectX::XMVECTOR inp_shapeColor)
{
    shapeColor = inp_shapeColor;
}

void Line::SetVec1(float v1x, float v1y)
{
    v1 = { v1x, v1y };
}

void Line::SetVec2(float v2x, float v2y)
{
    v2 = { v2x, v2y };
}