#pragma once

#include "pch.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Collider.h"
#include "InputManager.h"


// Make it be a part of game object.
class PlayerController : public Component {
private:
	InputManager* inputManager = InputManager::GetInstance();
	std::shared_ptr<GameObject> parentObj = nullptr; // Need it for applying movement.
	RigidBody* rb = nullptr; // need it for the jump force.
	Collider* collider = nullptr;	// Detect when the player hits an object. 
	float fSpeed = 2.f;

public:
	PlayerController(GameObject& inp_parentObj);

	void Awake() override;

	void Update(float deltaTime) override;

	void Movement();

	void Jump();
};