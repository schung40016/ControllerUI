#include "pch.h"
#include "SolidBox.h"
#include "Source/Game/GameObject.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/BoxCollider.h"

SolidBox::SolidBox()
{
	resourceManager = GameObjectManager::GetInstance();
}

SolidBox::SolidBox(float inp_size, std::string inp_boxName, DirectX::SimpleMath::Vector2 inp_position, float inp_width, float inp_length)
{
	resourceManager = GameObjectManager::GetInstance();
	sSolidBoxName = inp_boxName;
	fSizeMultiplier = inp_size;

	std::string sColliderName = sSolidBoxName + "_Collider";

	GameObject box = GameObject(sSolidBoxName, inp_position, fSizeMultiplier);
	GameObject& tempSolidBox = resourceManager->GetGameObj(sSolidBoxName);
	Quad groundShape = Quad(sSolidBoxName + "_Shape", DirectX::Colors::DarkGray, resourceManager->GetGameObj(sSolidBoxName), 1.f, 0, 0, inp_width, inp_length, true);
	std::vector<DirectX::SimpleMath::Vector2> solidBoxCollisionBox = FetchPositionPairs(inp_width, inp_length);

	BoxCollider boxCollider = BoxCollider(tempSolidBox, solidBoxCollisionBox, false);

	resourceManager->AddColliderObj(EnumData::ColliderLayers::Ground, sColliderName, boxCollider);

	tempSolidBox.SetComponents({
		&resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Ground][sColliderName]
	});
}

std::vector<DirectX::SimpleMath::Vector2> SolidBox::FetchPositionPairs(const float inp_width, const float inp_length)
{
	std::vector<DirectX::SimpleMath::Vector2> quadrants = { {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f} };
	std::vector<DirectX::SimpleMath::Vector2> results = {};

	for (DirectX::SimpleMath::Vector2 pair : quadrants)
	{
		results.push_back({ pair.x * inp_width, pair.y * inp_length });
	}

	return results;
}