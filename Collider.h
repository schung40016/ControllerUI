#pragma once

#include "pch.h"
#include "Component.h"
#include <GameObject.h>;

class Collider : public Component {
private:
	std::shared_ptr<GameObject> parentObj = nullptr;		// Need for determining the center point origin of our game object.
	bool canCollide = false;
	std::vector<DirectX::SimpleMath::Vector2> vertices = {};

public:
	Collider();

	DirectX::SimpleMath::Vector2 GetEdgeNormal(const DirectX::SimpleMath::Vector2& v1, const DirectX::SimpleMath::Vector2& v2);

	bool OverlapOnAxis(const Collider& rb2, const DirectX::SimpleMath::Vector2& axis);

	bool isColliding(Collider& rb2);

	bool CanCollide();

	bool setVertices();
};