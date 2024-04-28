#pragma once
#include "pch.h"
#include "GameObjectManager.h"

class Raycast {
public:
	static bool CastRaycast(DirectX::SimpleMath::Vector2 origin, DirectX::SimpleMath::Vector2 direction, int layer, float length);
};