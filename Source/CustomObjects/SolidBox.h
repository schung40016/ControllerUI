#pragma once

#include "pch.h"
#include "Source/Game/GameObject.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/BoxCollider.h"

class SolidBox
{
private:
	GameObjectManager* resourceManager = nullptr;
	std::string sSolidBoxName = "";
	int fSizeMultiplier = 975.f;

public:
	SolidBox();

	SolidBox(float inp_size, std::string inp_boxName, DirectX::SimpleMath::Vector2 inp_position, float inp_width, float inp_length);

	std::vector<DirectX::SimpleMath::Vector2> FetchPositionPairs(const float inp_width, const float inp_length);
};