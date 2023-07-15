#include "pch.h"
#include "Line.h"

Line::Line()
{
}

Line::Line(DirectX::XMVECTOR inp_shapeColor, IDirXObject& inp_parentObj, float inp_offsetX, float inp_offsetY, float inp_scale)
    : shapeColor(inp_shapeColor)
{
    m_parentObj = &inp_parentObj;
    m_offsetPos = {inp_offsetX, inp_offsetY};
    m_scale = inp_scale;
}

Line::Line(DirectX::XMVECTOR inp_shapeColor, float v1x, float v1y, float v2x, float v2y, float inp_scale)
	: shapeColor(inp_shapeColor)
{
    m_position = { v1x, v1y };
    point2 = { v2x, v2y };
    m_scale = inp_scale;
}

void Line::DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch)
{
    float calcX = point2.x * m_scale + m_position.x;
    float calcY = point2.y * m_scale * -1 + m_position.y;

    DirectX::DX12::VertexPositionColor vec1(Vector3(m_position.x, m_position.y, 0.f), shapeColor);
    DirectX::DX12::VertexPositionColor vec2(Vector3(calcX, calcY, 0.f), shapeColor);
    m_batch->DrawLine(vec1, vec2);
}

// Getters & Setters
DirectX::SimpleMath::Vector2 Line::GetPoint2()
{
    return point2;
}

void Line::SetPoint2(float v2x, float v2y)
{
     point2 = { v2x, v2y };
}