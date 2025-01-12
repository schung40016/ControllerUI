#include "pch.h"
#include "Raycast.h"
#include "Source/Managers/GameObjectManager.h"

bool Raycast::CastRaycast(DirectX::SimpleMath::Vector2 origin, DirectX::SimpleMath::Vector2 direction, int layer, float length)
{
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	std::unordered_map<std::string, BoxCollider> currColliderObjectLayer = resourceManager->GetColliderObjBank()[layer];

	DirectX::SimpleMath::Vector2 line_r2s = origin;
	DirectX::SimpleMath::Vector2 line_r2e = (-1 * length * direction) + origin;

	for (auto& curr_collider : currColliderObjectLayer)
	{
		std::vector<DirectX::SimpleMath::Vector2> currentColliderWorld = curr_collider.second.GetWorldPositions();

		// against the other polygon's edges.
		for (int q = 0; q < currentColliderWorld.size(); q++)
		{
			DirectX::SimpleMath::Vector2 line_r1s = currentColliderWorld[q];
			DirectX::SimpleMath::Vector2 line_r1e = currentColliderWorld[(q + 1) % currentColliderWorld.size()];	// neighboring point.

			// Standdard "off the shelf" line segment intersection.
			float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
			float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
			float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

			if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
			{
				return true;
			}
		}
	}
	return false;
}