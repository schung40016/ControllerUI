#pragma once

#include "pch.h"
#include "Source/UI_Objects/Line.h"

static class WireFrame
{
public:
	WireFrame();

	static void SetWireFrame(GameObject& inp_parentObj, std::string name, std::vector<DirectX::SimpleMath::Vector2>& inp_vertexLines, DirectX::XMVECTORF32 color, int layer = 0);
};