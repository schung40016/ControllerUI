#pragma once

#include "pch.h";
#include "RigidBody.h";

void RigidBody::Update(float deltaTime)		// Performs all calculations.
{
	ApplyGravity(deltaTime);
	ApplyForce(deltaTime);
}

RigidBody::RigidBody(GameObject& inp_parentObj, bool inp_isKinematic, float inp_fMass, 
	float inp_fAcceleration) : bIsKinematic(bIsKinematic), fMass(inp_fMass), fAcceleration(inp_fAcceleration)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
}

void RigidBody::ApplyGravity(float deltaTime)
{
	// Apply gravity here.
	if (bIsKinematic)
	{
		DirectX::SimpleMath::Vector2 calcPos = parentObj->GetPosition() + velocity * deltaTime;

		parentObj->SetPosition(calcPos);
		velocity = velocity + gravityVelocity * deltaTime;
	}
}

int RigidBody::GetLayerMask() const
{
	return parentObj->GetLayerMask();
}

float RigidBody::GetMass()
{
	return fMass;
}

// Need to add a player controller

void RigidBody::AddForce(DirectX::SimpleMath::Vector2 inp_force)
{
	accumulatedForce += inp_force;
}

void RigidBody::ApplyForce(float deltaTime)
{
	// Apply resistance to the velocity overtime.
	velocity *= (1.0f - fDamping * deltaTime);
	// Apply added force.
	velocity += (accumulatedForce / fMass) * deltaTime;
	// Reset accumulatedForce for the next time it is called.
	accumulatedForce = { 0, 0 };
	// Update parent object's position.
	DirectX::SimpleMath::Vector2 parentPos = parentObj->GetPosition();
	parentPos += velocity * deltaTime;
	parentObj->SetPosition(parentPos);
}