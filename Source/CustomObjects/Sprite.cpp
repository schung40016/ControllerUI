#pragma once

#include "pch.h"

struct Sprite {
	std::string sName = "";
	DirectX::SimpleMath::Vector2 origin = {};
	RECT sourceRect = {};
};