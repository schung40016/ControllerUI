#pragma once

#include "pch.h"
#include "../Constants/DefaultValues.h"

class Player 
{
private:
	std::string sPlayerName = "";
	float fSizeMultiplier = DefaultValues::DEFAULT_SIZE;

public:
	Player();

	Player(float inp_size, std::string inp_playerName, DirectX::SimpleMath::Vector2 inp_position, float inp_width, float inp_length);

	std::vector<DirectX::SimpleMath::Vector2> FetchPositionPairs(const float inp_width, const float inp_length);

	std::string GetPlayerName();
};