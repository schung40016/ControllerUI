#include "pch.h"
#include "Quad.h"
#include "Source/Managers/GameObjectManager.h"

// Constructor
Quad::Quad()
{
	resourceManager = GameObjectManager::GetInstance();
}

Quad::Quad(std::string id, DirectX::XMVECTOR colorInput, GameObject& inp_parentObj, float inp_scale, float inp_x, float inp_y, float inp_len, float inp_wid, bool inp_display)
{
	SetName(id);
	SetColor(colorInput);
	SetParent(inp_parentObj);
	SetScale(inp_scale);
	SetPosition({ inp_x, inp_y });
	SetLength(inp_len);
	SetWidth(inp_wid);
	SetDisplay(inp_display);
	resourceManager->AddQuadObj(id, *this);
}

void Quad::Draw(const std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>& inp_batch) const 
{
	if (GetDisplay() == false)
	{
		return;
	}

	DirectX::SimpleMath::Vector2 newPos = GetRenderPosition();
	float currScale = GetScale();

	float calcLen = GetLength() / 2.0f;
	float calcWid = GetWidth() / 2.0f;

	DirectX::XMVECTOR currColor = GetColor();

	DirectX::VertexPositionColor v1(DirectX::SimpleMath::Vector3(newPos.x + calcLen * currScale, newPos.y - calcWid * currScale, 0.f), currColor);	// problem: quad's parent points to the gameobj in world.h, and gameobjectmanager holds a new copy.
	DirectX::VertexPositionColor v2(DirectX::SimpleMath::Vector3(newPos.x + calcLen * currScale, newPos.y + calcWid * currScale, 0.f), currColor);
	DirectX::VertexPositionColor v3(DirectX::SimpleMath::Vector3(newPos.x - calcLen * currScale, newPos.y + calcWid * currScale, 0.f), currColor);
	DirectX::VertexPositionColor v4(DirectX::SimpleMath::Vector3(newPos.x - calcLen * currScale, newPos.y - calcWid * currScale, 0.f), currColor);

	inp_batch->DrawQuad(v1, v2, v3, v4);
}

// Destructor
Quad::~Quad()
{
}
