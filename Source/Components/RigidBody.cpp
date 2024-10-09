#pragma once

#include "pch.h";
#include "RigidBody.h";

RigidBody::RigidBody()
{}

void RigidBody::Update(float deltaTime)		// Performs all calculations.
{
	CheckIfGrounded();
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
	if (bIsKinematic && !grounded)
	{
		DirectX::SimpleMath::Vector2 calcPos = parentObj->GetPosition() + velocity * deltaTime;

		parentObj->SetPosition(calcPos);
		velocity = velocity + gravityVelocity * deltaTime * fMass;
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
	actVelocity.x = Interpolate(velocity.x, actVelocity.x, deltaTime * smoothness);
	actVelocity.y = Interpolate(velocity.y, actVelocity.y, deltaTime * smoothness);

	parentObj->MovePosition(actVelocity);
}

float RigidBody::Interpolate(float goalPosition, float currPosition, float dt)
{
	float pos_diff = goalPosition - currPosition;

	if (pos_diff > dt)
	{
		velocity.y = 0.f;
		return currPosition + dt;
	}
	if (pos_diff < -dt)
	{
		return currPosition - dt;
	}
	return goalPosition;
}

void RigidBody::CheckIfGrounded()
{
	grounded = Raycast::CastRaycast(parentObj->GetPosition(), { 0, -1 }, EnumData::ColliderLayers::Ground, 27.f);
}

boolean RigidBody::isGrounded()
{
	return grounded;
}

DirectX::SimpleMath::Vector2 RigidBody::GetVelocity() const
{
	return velocity;
}

DirectX::SimpleMath::Vector2 RigidBody::GetAcceleration() const
{
	return accumulatedForce;
}