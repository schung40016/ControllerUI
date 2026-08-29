#include "pch.h"
#include "Box.h"
#include "Source/Game/GameObject.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/BoxCollider.h"
#include "../Constants/DefaultValues.h"

Box::Box()
{
}

Box::Box(float size, std::string boxName, DirectX::SimpleMath::Vector2 position, float width, float length, bool isColliding)
	: sBoxName(boxName), v2Position(position), fWidth(width), fLength(length), bIsColliding(isColliding)
{
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	sBoxName = boxName;
	fSizeMultiplier = size;

	std::string sColliderName = sBoxName + "_Collider";

	GameObject box(sBoxName, position, fSizeMultiplier);
	GameObject& tempBox = resourceManager->Get<GameObject>(sBoxName);
	Quad quad(sBoxName + "_Shape", DirectX::Colors::DarkGray, resourceManager->Get<GameObject>(sBoxName), 1.f, 0, 0, width, length, true);

	if (isColliding)
	{
		std::vector<DirectX::SimpleMath::Vector2> BoxCollisionBox = FetchPositionPairs(width, length);

		BoxCollider boxCollider = BoxCollider(tempBox, BoxCollisionBox, false);

		resourceManager->AddColliderObj(EnumData::ColliderLayers::Ground, sColliderName, boxCollider);

		tempBox.SetComponents({
			&resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Ground][sColliderName]
			});
	}

	resourceManager->Add<Box>(boxName, *this);
}

std::vector<DirectX::SimpleMath::Vector2> Box::FetchPositionPairs(const float width, const float length)
{
	// {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f}
	std::vector<DirectX::SimpleMath::Vector2> quadrants = { {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f} };
	std::vector<DirectX::SimpleMath::Vector2> results = {};

	for (DirectX::SimpleMath::Vector2 pair : quadrants)
	{
		results.push_back({ pair.x * width, pair.y * length });
	}

	return results;
}