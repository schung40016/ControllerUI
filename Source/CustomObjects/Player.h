#pragma once

#include "pch.h"

class Player 
{
private: 
	class GameObjectManager* resourceManager = nullptr;
	std::string sPlayerName = "";
	float fSizeMultiplier = 975.f;

public:
	Player();

	Player(float inp_size, std::string inp_playerName, DirectX::SimpleMath::Vector2 inp_position, float inp_width, float inp_length);

	std::vector<DirectX::SimpleMath::Vector2> FetchPositionPairs(const float inp_width, const float inp_length);
};