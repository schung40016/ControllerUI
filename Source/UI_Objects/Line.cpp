#include "pch.h"
#include "Line.h"
#include "Source/Managers/GameObjectManager.h"

Line::Line()
{
    resourceManager = GameObjectManager::GetInstance();
}

Line::Line(std::string id, DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, DirectX::SimpleMath::Vector2 inp_pt2, float inp_scale, bool inp_isStatic, float inp_z)
{
    SetName(id);
    SetParent(inp_parentObj);
    SetScale(inp_scale);
    SetPosition(DirectX::SimpleMath::Vector3(inp_pt2.x, inp_pt2.y, inp_z));
    SetColor(inp_shapeColor);
    SetIsStatic(inp_isStatic);
    resourceManager->Add<Line>(id, *this);
}

Line::Line(std::string id, DirectX::XMVECTOR inp_shapeColor, GameObject& inp_parentObj, DirectX::SimpleMath::Vector2 inp_pt1, DirectX::SimpleMath::Vector2 inp_pt2, float inp_scale, bool inp_isStatic, int inp_layer, float inp_z)
    : layer(inp_layer)
{
    SetName(id);
    SetParent(inp_parentObj);
    SetPosition(DirectX::SimpleMath::Vector3(inp_pt1.x, inp_pt1.y, inp_z));
    point1 = inp_pt1;
    point2 = inp_pt2;
    SetScale(inp_scale);
    SetColor(inp_shapeColor);
    SetIsStatic(inp_isStatic);
    resourceManager->Add<Line>(id, *this);
}

void Line::DrawStickOrientation(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch, const DirectX::SimpleMath::Vector2& camOffset) const
{
    Vector2 pos = GetRenderPosition();

    if (GetIsStatic())
    {
        pos += camOffset;
    }

    float calcPt2X = (pos.x - point1.x) + point2.x;
    float calcPt2Y = (pos.y + point1.y) - point2.y;

    DirectX::DX12::VertexPositionColor vec1(Vector3(pos.x, pos.y, layer), GetColor());
    DirectX::DX12::VertexPositionColor vec2(Vector3(calcPt2X, calcPt2Y, layer), GetColor());
    m_batch->DrawLine(vec1, vec2);
}

// Getters & Setters
DirectX::SimpleMath::Vector2 Line::GetPoint2()
{
    return point2;
}

DirectX::SimpleMath::Vector2 Line::GetDimensions() const
{
    return { abs(point2.x - point1.x), abs(point2.y - point1.y) };
}

void Line::SetPoint2(float v2x, float v2y)
{
     point2 = { v2x, v2y };
}