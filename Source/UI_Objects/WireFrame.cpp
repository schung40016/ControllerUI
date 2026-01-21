#include "pch.h"
#include "WireFrame.h"

WireFrame::WireFrame()
{
}

void WireFrame::SetWireFrame(GameObject& inp_parentObj, std::string name, std::vector<DirectX::SimpleMath::Vector2>& inp_vertexLines, DirectX::XMVECTORF32 color, int layer)
{
	std::string parentName = inp_parentObj.GetName() + " " + name + " - WireFrameLine ";

	for (int i = 0; i < inp_vertexLines.size(); ++i)
	{
		std::string colliderName = parentName + std::to_string(i);

		auto temp = new Line(colliderName, color, inp_parentObj, inp_vertexLines[i], inp_vertexLines[(i + 1) % inp_vertexLines.size()], 1.0f, false, layer);
	}
}
