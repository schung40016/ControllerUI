#pragma once

#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Raycast.h"

class RigidBody : public Component {
private:
	std::shared_ptr<GameObject> parentObj = nullptr;		// Need for determining the center point origin of our game object.
	bool bIsKinematic = false;								// Determines if the object is effected by physics.
	float fMass = 1.0f;
	float fAcceleration = -9.81f;							// Copy Earths gravity.
	float fDamping = 0.1f;
	DirectX::SimpleMath::Vector2 velocity = {0.f, 0.f};		// vector pointing to right.
	DirectX::SimpleMath::Vector2 gravityVelocity = { 0.f, fAcceleration };
	DirectX::SimpleMath::Vector2 accumulatedForce = { 0, 0 };
	DirectX::SimpleMath::Vector2 actVelocity = { 0, 0 };
	DirectX::SimpleMath::Vector2 totalGoalVelocity = { 0, 0 };
	float smoothness = 10.f;
	

	// Grounded variables.
	boolean grounded = false;
	float isGroundedErrorMargin = 0.1f;
	DirectX::SimpleMath::Vector2 prevPosition = { 0, 0 };


public:
	RigidBody(GameObject& inp_parentObj, bool inp_isKinematic = false, float inp_fMass = 1.0f, float fAcceleration = 1.0f);

	void Update(float deltaTime) override;		// Calls all relevant functions for calculations.

	void ApplyGravity(float deltaTime);

	int GetLayerMask() const;

	float GetMass();

	void AddForce(DirectX::SimpleMath::Vector2 force);

	void ApplyForce(float deltaTime);

	float Interpoplate(float goalPosition, float currPosition, float dt);

	void CheckIfGrounded();

	boolean isGrounded();
};