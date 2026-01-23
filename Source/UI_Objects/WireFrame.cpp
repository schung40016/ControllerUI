#include "pch.h"
#include "WireFrame.h"
#include "Source/Managers/GameObjectManager.h"

WireFrame::WireFrame()
{
}

void WireFrame::SetWireFrame(GameObject& parentObj, std::string name, std::vector<DirectX::SimpleMath::Vector2>& vertexLines, DirectX::XMVECTORF32 color, int layer)
{
	std::string parentName = parentObj.GetName() + " " + name + " - WireFrameLine ";

	for (int i = 0; i < vertexLines.size(); ++i)
	{
		std::string colliderName = parentName + std::to_string(i);

		auto temp = new Line(colliderName, color, parentObj, vertexLines[i], vertexLines[(i + 1) % vertexLines.size()], 1.0f, false, layer);
	}
}

void WireFrame::SetEdgeColor(GameObject& parentObj, std::string name, DirectX::XMVECTORF32 color, int index)
{
	if (index < 0)
	{
		return;
	}

	std::string parentName = parentObj.GetName() + " " + name + " - WireFrameLine " + std::to_string(index);

	GameObjectManager::GetInstance()->GetLnObj(parentName).SetColor(color);
}