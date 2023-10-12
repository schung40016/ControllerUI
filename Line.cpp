#include "pch.h"
#include "Line.h"

Line::Line()
{
}

Line::Line(DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale)
    : shapeColor(inp_shapeColor)
{
    SetParent(inp_parentObj);
    SetScale(inp_scale);
    SetPosition(inp_x, inp_y );
}

Line::Line(DirectX::XMVECTOR inp_shapeColor, float v1x, float v1y, float v2x, float v2y, float inp_scale)
	: shapeColor(inp_shapeColor)
{
    SetPosition(v1x, v1y);
    point2 = { v2x, v2y };
    SetScale(inp_scale);
}

void Line::DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch) const
{
    Vector2 pos = GetPosition();
    float currScale = GetScale();
    float calcX = point2.x * lineSizeMultiplier * currScale + pos.x;
    float calcY = point2.y * lineSizeMultiplier * currScale * -1 + pos.y;
    std::cout << pos.x << ", " << pos.y << std::endl;

    DirectX::DX12::VertexPositionColor vec1(Vector3(pos.x, pos.y, 0.f), shapeColor);
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