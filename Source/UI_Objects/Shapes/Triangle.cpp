#include "pch.h"
#include "Triangle.h"
#include "Source/Managers/GameObjectManager.h"

// Constructor
Triangle::Triangle()
{
	resourceManager = GameObjectManager::GetInstance();
}

// Create a instance of an equallateral triangle at a specified position.
Triangle::Triangle(std::string id, DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float inp_scale, float inp_x, float inp_y, float inp_len, float inp_wid)
{
	SetName(id);
	SetColor(colorInput);
	SetParent(inp_parentObj);
	SetScale(inp_scale);
	SetPosition({ inp_x, inp_y });
	SetLength(inp_len);
	SetWidth(inp_wid);
	resourceManager->AddTriObj(id, *this);
}

// Draw Triangle.
void Triangle::Draw(const std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& inp_batch) const
{
	if (GetDisplay() == false)
	{
		return;
	}

	DirectX::SimpleMath::Vector2 newPos = GetPositionActual();
	float currScale = GetScale();

	float calcLen = GetLength() / 2.0f;
	float calcWid = GetWidth() / 2.0f;

	DirectX::XMVECTOR currColor = GetColor();

	VertexPositionColor v1(Vector3(newPos.x, newPos.y - calcLen * currScale, 0.f), currColor);
	VertexPositionColor v2(Vector3(newPos.x + calcWid * currScale, newPos.y + calcLen * currScale, 0.f), currColor);
	VertexPositionColor v3(Vector3(newPos.x - calcWid * currScale, newPos.y + calcLen * currScale, 0.f), currColor);

	inp_batch->DrawTriangle(v1, v2, v3);
}

// Destructor
Triangle::~Triangle()
{
}
