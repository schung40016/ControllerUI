#pragma once

#include "pch.h"
#include "Source/Game/GameObject.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Managers/InputManager.h"


// Make it be a part of game object.
class PlayerController : public Component {
private:
	InputManager* inputManager = InputManager::GetInstance();
	std::shared_ptr<GameObject> parentObj = nullptr; // Need it for applying movement.
	RigidBody* rb = nullptr; // need it for the jump force.
	BoxCollider collider;	// Detect when the player hits an object. 
	float fSpeed = 2.f;
	float fJumpHeight = 15.f;

public:
	PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider);

	void Awake() override;

	void Update(float deltaTime) override;

	void Movement(float dt);

	void Jump();
};