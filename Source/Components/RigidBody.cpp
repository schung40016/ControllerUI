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

	StopVelocity();
}

void RigidBody::StopVelocity()
{
	if ((grounded && actVelocity.y > 0) || (topGrounded && actVelocity.y < 0))
	{
		actVelocity.y = 0;
	}

	if ((rightGrounded && actVelocity.x > 0) || (leftGrounded && actVelocity.x < 0))
	{
		actVelocity.x = 0;
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
	// Update acceleration.
	totalGoalVelocity = (velocity - actVelocity) / deltaTime;

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
	float parentWidthHalved = parentObj->GetSize().x / 2.f;
	float rayCastLength = parentWidthHalved + 2.f;

	DirectX::SimpleMath::Vector2 parentPos = parentObj->GetPosition();
	DirectX::SimpleMath::Vector2 rightEdge = { parentPos.x + parentWidthHalved, parentPos.y};
	DirectX::SimpleMath::Vector2 leftEdge = { parentPos.x - parentWidthHalved, parentPos.y };
	bool groundedRightCheck = Raycast::CastRaycast(rightEdge, { 0, -1 }, EnumData::ColliderLayers::Ground, rayCastLength);
	bool groundedLeftCheck = Raycast::CastRaycast(leftEdge, { 0, -1 }, EnumData::ColliderLayers::Ground, rayCastLength);

	leftGrounded = Raycast::CastRaycast(parentPos, { 1, 0 }, EnumData::ColliderLayers::Ground, rayCastLength);
	rightGrounded = Raycast::CastRaycast(parentPos, { -1, 0 }, EnumData::ColliderLayers::Ground, rayCastLength);
	topGrounded = Raycast::CastRaycast(parentPos, { 0, 1 }, EnumData::ColliderLayers::Ground, rayCastLength);

	grounded = groundedRightCheck || groundedLeftCheck;
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
	return totalGoalVelocity;
}