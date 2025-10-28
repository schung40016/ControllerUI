#pragma once

#include "pch.h"
#include "Component.h"
#include "Source/UI_Objects/Line.h"

class GameObject;

class BoxCollider : public Component {
private:
	std::shared_ptr<GameObject> parentObj = nullptr;		// Need for determining the center point origin of our game object.
	bool canCollide = false;
	bool isMovable = false;
	std::vector<DirectX::SimpleMath::Vector2> localVertices = {};	// FOr storing local point positions.
	std::vector<DirectX::SimpleMath::Vector2> worldVertices = {};	// FOr storing world point positions.
	DirectX::SimpleMath::Vector2 displacementDisplay = {0, 0};
	DirectX::SimpleMath::Vector2 totalDisplacement = {0, 0};
	std::vector<Line> vertexLines = {};
	class GameObjectManager* resourceManager = nullptr;

public:
	void Update(float deltaTime) override;

	BoxCollider();

	BoxCollider(GameObject& inp_parentObj, std::vector<DirectX::SimpleMath::Vector2>& inp_vertices, bool inp_isMovable);

	std::vector<DirectX::SimpleMath::Vector2> GetWorldPositions();

	std::shared_ptr<GameObject> GetParent() const;

	DirectX::SimpleMath::Vector2 GetEdgeNormal(const DirectX::SimpleMath::Vector2& v1, const DirectX::SimpleMath::Vector2& v2) const;

	bool IsColliding_SAT(class BoxCollider& other);

	// Good for dealing with shapes that have concave corners.
	bool IsColliding_DIAG(class BoxCollider& other);

	// An alternative to the original function that also fixes the collision problem.
	bool IsColliding_DIAG_STATIC(class BoxCollider& other);

	bool IsColliding_SAT_STATIC(BoxCollider& other);

	bool IsColliding_Simplified(std::vector<DirectX::SimpleMath::Vector2>& predictedVertices, BoxCollider& other);

	bool CanCollide();

	bool CollidesWithLayer(int layer);

	bool PredictedCollidesWithLayer(std::vector<DirectX::SimpleMath::Vector2>& predictedVertices, int layer);

	void SetWorldPositions();

	DirectX::SimpleMath::Vector2 GetTotalDisplacement();

	void ResetTotalDisplacement();

	DirectX::SimpleMath::Vector2 GetDisplacement();
};