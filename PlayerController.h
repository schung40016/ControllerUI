#pragma once

#include "pch.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Collider.h"

class PlayerController : Component {
private:
	std::shared_ptr<GameObject> parentObj = nullptr; // Need it for applying movement.
	RigidBody* rb = nullptr; // need it for the jump force.
	Collider* collider = nullptr;	// Detect when the 
public:
	void Update();

	void Movement();

	void Jump();
};