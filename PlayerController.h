#pragma once

#include "pch.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "InputManager.h"


// Make it be a part of game object.
class PlayerController : public Component {
private:
	InputManager* inputManager = InputManager::GetInstance();
	std::shared_ptr<GameObject> parentObj = nullptr; // Need it for applying movement.
	RigidBody* rb = nullptr; // need it for the jump force.
	BoxCollider collider;	// Detect when the player hits an object. 
	float fSpeed = 2.f;
	DirectX::SimpleMath::Vector2 actVelocity = { 0, 0 };
	DirectX::SimpleMath::Vector2 goalVelocity = { 0, 0 };

public:
	PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider);

	void Awake() override;

	void Update(float deltaTime) override;

	void Movement(float dt);

	void Jump();

	float Interpoplate(float goalPosition, float currPosition, float dt);
};