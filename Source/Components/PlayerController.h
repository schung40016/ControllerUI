#pragma once

#include "pch.h"
#include "Component.h"
#include "BoxCollider.h"

class RigidBody;
class GameObject;

class PlayerController : public Component {
private:
	class InputManager* inputManager = nullptr;
	std::shared_ptr<class GameObject> parentObj = nullptr;
	class Image* playerSprite = nullptr;
	RigidBody* rb = nullptr;								// Applies physics on gameobject.
	class AnimationController* ac = nullptr;						// Animates gameobject given state.
	BoxCollider collider;									// Collision detection. 
	float fSpeed = 50.f;
	float fJumpHeight = 100.f;

public:
	PlayerController();

	PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider, float inp_speed = 50.f, float inp_jumpHeight = 2000.0f);

	void Awake() override;

	void Update(float deltaTime) override;

	void Movement(float dt);

	void Jump();

	void UpdateState();
};