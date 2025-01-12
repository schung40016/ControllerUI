#pragma once

#include "pch.h"
#include "Component.h"
#include "BoxCollider.h"

class RigidBody;
class GameObject;

// Make it be a part of game object.
class PlayerController : public Component {
private:
	class InputManager* inputManager = nullptr;
	std::shared_ptr<class GameObject> parentObj = nullptr; // Need it for applying movement.
	class Image* playerSprite = nullptr;
	RigidBody* rb = nullptr; // need it for the jump force.
	BoxCollider collider;	// Detect when the player hits an object. 
	float fSpeed = 50.f;
	float fJumpHeight = 10000.f;

public:
	PlayerController();

	PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider, float inp_speed = 50.f, float inp_jumpHeight = 2000.0f);

	void Awake() override;

	void Update(float deltaTime) override;

	void Movement(float dt);

	void Jump();
};

// link error, something to do with imports.
// Forward declaration in header files and import in cpp.