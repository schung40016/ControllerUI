#pragma once

#include "pch.h"

class SolidBox
{
private:
	class GameObjectManager* resourceManager = nullptr;
	std::string sSolidBoxName = "";
	float fSizeMultiplier = 975.f;

public:
	SolidBox();

	SolidBox(float inp_size, std::string inp_boxName, DirectX::SimpleMath::Vector2 inp_position, float inp_width, float inp_length);

	std::vector<DirectX::SimpleMath::Vector2> FetchPositionPairs(const float inp_width, const float inp_length);
};