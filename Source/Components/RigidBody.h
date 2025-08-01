#pragma once

#include "pch.h"
#include "Component.h"

class GameObject;

class RigidBody : public Component {
private:
	std::shared_ptr<GameObject> parentObj = nullptr;		// Need for determining the center point origin of our game object.
	bool bIsKinematic = false;								// Determines if the object is effected by physics.
	float fMass = 1.0f;
	float fAcceleration = -9.81f;							// Copy Earths gravity.
	float fDamping = 2.5f;
	float fSmoothness = 1000.f;
	float fGroundCheckerOffset = 2.f;
	DirectX::SimpleMath::Vector2 velocity = {0.f, 0.f};		// vector pointing to right.
	DirectX::SimpleMath::Vector2 gravityAcceleration = { 0.f, fAcceleration * 2};
	DirectX::SimpleMath::Vector2 accumulatedForce = { 0, 0 };
	DirectX::SimpleMath::Vector2 actVelocity = { 0, 0 };
	DirectX::SimpleMath::Vector2 totalGoalVelocity = { 0, 0 };

	// Grounded variables.
	bool grounded, rightGrounded, leftGrounded, topGrounded = false;
	float isGroundedErrorMargin = 0.1f;
	DirectX::SimpleMath::Vector2 prevPosition = { 0, 0 };

public:
	RigidBody();

	RigidBody(GameObject& inp_parentObj, bool inp_isKinematic = false, float inp_fMass = 1.0f, float fAcceleration = 1.0f);

	void Update(float deltaTime) override;		// Calls all relevant functions for calculations.

	void ApplyGravity(float deltaTime);

	void StopVelocity();

	void AddForce(DirectX::SimpleMath::Vector2 force);

	void ApplyForce(float deltaTime);

	float Interpolate(float goalPosition, float currPosition, float dt);

	void CheckIfGrounded();

	// Getters
	boolean isGrounded();

	int GetLayerMask() const;

	float GetMass();

	DirectX::SimpleMath::Vector2 GetVelocity() const;

	DirectX::SimpleMath::Vector2 GetAcceleration() const;
};