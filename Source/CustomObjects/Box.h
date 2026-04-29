#pragma once

#include "pch.h"

class Box
{
private:
	std::string sBoxName = "";
	DirectX::SimpleMath::Vector2 v2Position = { 0, 0 };
	float fWidth = 0.f;
	float fLength = 0.f;
	float fSizeMultiplier = 975.f;
	bool bIsColliding = false;

public:
	Box();

	Box(float size, std::string boxName, DirectX::SimpleMath::Vector2 position, float width = 100.f, float length = 100.f, bool isColliding = false);

	std::vector<DirectX::SimpleMath::Vector2> FetchPositionPairs(const float width, const float length);
};