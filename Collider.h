#pragma once

#include "pch.h"
#include "Component.h"
#include <GameObject.h>;
#include <Line.h>

class Collider : public Component {
private:
	std::shared_ptr<GameObject> parentObj = nullptr;		// Need for determining the center point origin of our game object.
	bool canCollide = false;
	std::vector<DirectX::SimpleMath::Vector2> vertices = {};
	std::vector<Line> vertexLines = {};

public:
	void Update(float deltaTime) override;

	Collider(GameObject& inp_parentObj, std::vector<DirectX::SimpleMath::Vector2>& inp_vertices);

	DirectX::SimpleMath::Vector2 GetEdgeNormal(const DirectX::SimpleMath::Vector2& v1, const DirectX::SimpleMath::Vector2& v2);

	bool OverlapOnAxis(const Collider& rb2, const DirectX::SimpleMath::Vector2& axis);

	bool isColliding(Collider& rb2);

	bool CanCollide();

	bool setVertices();
};