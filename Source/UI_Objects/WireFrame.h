#pragma once

#include "pch.h"
#include "Source/UI_Objects/Line.h"

static class WireFrame
{
public:
	WireFrame();

	static void SetWireFrame(GameObject& parentObj, std::string name, std::vector<DirectX::SimpleMath::Vector2>& vertexLines, DirectX::XMVECTORF32 color, int layer = 0);

	static void SetEdgeColor(GameObject& parentObj, std::string name, DirectX::XMVECTORF32 color, int index);
};