#include "pch.h"
#include "Line.h"
#include "GameObjectManager.h"

Line::Line()
{
    resourceManager = GameObjectManager::GetInstance();
}

Line::Line(std::string id, DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, DirectX::SimpleMath::Vector2 inp_pt2, float inp_scale)
    : shapeColor(inp_shapeColor)
{
    SetName(id);
    SetParent(inp_parentObj);
    SetScale(inp_scale);
    SetPosition(inp_pt2);
    shapeColor = inp_shapeColor;
    resourceManager->AddLnObj(id, *this);
}

Line::Line(std::string id, DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, DirectX::SimpleMath::Vector2 inp_pt1, DirectX::SimpleMath::Vector2 inp_pt2, float inp_scale)
{
    SetName(id);
    SetParent(inp_parentObj);
    SetPosition(inp_pt1);
    point1 = inp_pt1;
    point2 = inp_pt2;
    SetScale(inp_scale);
    shapeColor = inp_shapeColor;
    resourceManager->AddLnObj(id, *this);
}

void Line::DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch) const
{
    Vector2 pos = GetPosition();
    //float calcX = point2.x * lineSizeMultiplier * currScale + pos.x;
    //float calcY = point2.y * lineSizeMultiplier * currScale * 1 + pos.y;

    float calcPt1X = pos.x + point1.x;
    float calcPt1Y = pos.y + point1.y;
    float calcPt2X = pos.x + point2.x;
    float calcPt2Y = pos.y + point2.y;

    DirectX::DX12::VertexPositionColor vec1(Vector3(calcPt1X, calcPt1Y, 1.f), shapeColor);
    DirectX::DX12::VertexPositionColor vec2(Vector3(calcPt2X, calcPt2Y, 1.f), shapeColor);
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