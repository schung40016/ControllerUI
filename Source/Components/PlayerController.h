#pragma once

#include "pch.h"
#include "Component.h"
#include "Source/Game/GameObject.h"
#include "Source/Managers/InputManager.h"
#include "Source/Components/BoxCollider.h"

class RigidBody;

// Make it be a part of game object.
class PlayerController : public Component {
private:
	InputManager* inputManager = InputManager::GetInstance();
	std::shared_ptr<GameObject> parentObj = nullptr; // Need it for applying movement.
	RigidBody* rb = nullptr; // need it for the jump force.
	BoxCollider collider;	// Detect when the player hits an object. 
	float fSpeed = 50.f;
	float fJumpHeight = 2000.f;

public:
	PlayerController();

	PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider, float inp_speed = 50.f, float inp_jumpHeight = 2000.0f);

	void Awake() override;

	void Update(float deltaTime) override;

	void Movement(float dt);

	void Jump();
};